// Marketplace + Editor - mock local app (no backend). Seed + simple CRUD + sync simulation.
// WARNING: designed as prototype. Replace localStorage with real API calls when integrating.

const STORAGE_KEY = 'artaround_db_v1';
const DEFAULT_USERS = [
  {id:'autore1', role:'author', pwd:'12345678'},
  {id:'autore2', role:'author', pwd:'12345678'},
  {id:'visitatore1', role:'visitor', pwd:'12345678'},
  {id:'visitatore2', role:'visitor', pwd:'12345678'}
];

// ---------- DOM ----------
const userSelect = document.getElementById('userSelect');
const logoutBtn = document.getElementById('logoutBtn');
const museumSelect = document.getElementById('museumSelect');
const itemsList = document.getElementById('itemsList');
const searchInput = document.getElementById('searchInput');
const filterTone = document.getElementById('filterTone');
const newItemBtn = document.getElementById('newItemBtn');
const editorPanel = document.getElementById('editorPanel');
const itemForm = document.getElementById('itemForm');
const cancelEditBtn = document.getElementById('cancelEditBtn');
const saveItemBtn = document.getElementById('saveItemBtn');
const publishBtn = document.getElementById('publishBtn');
const visitsList = document.getElementById('visitsList');
const newVisitBtn = document.getElementById('newVisitBtn');
const syncVisitSelect = document.getElementById('syncVisitSelect');
const sessionCode = document.getElementById('sessionCode');
const startSessionBtn = document.getElementById('startSessionBtn');
const stopSessionBtn = document.getElementById('stopSessionBtn');
const studentCount = document.getElementById('studentCount');
const sessionLog = document.getElementById('sessionLog');

// form fields
const fObjectId = document.getElementById('itemObjectId');
const fTitle = document.getElementById('itemTitle');
const fAuthor = document.getElementById('itemAuthor');
const fLicense = document.getElementById('itemLicense');
const fPrice = document.getElementById('itemPrice');
const fDuration = document.getElementById('itemDuration');
const fImage = document.getElementById('itemImage');
const fTone = document.getElementById('itemTone');
const f3 = document.getElementById('text3');
const f15 = document.getElementById('text15');
const f40 = document.getElementById('text40');

let db = null;
let currentUser = null;
let editingItemId = null;
let activeSession = null; // {code, visitId, startedAt, connections:[]}

// ---------- Storage helpers ----------
function loadDB(){
  const raw = localStorage.getItem(STORAGE_KEY);
  if(raw) return JSON.parse(raw);
  // seed
  const museum = { id:'mambo', title:'Pinacoteca Demo', cover:'https://picsum.photos/seed/museo/800/300', desc:'Museo demo' };
  const artworks = [];
  for(let i=1;i<=10;i++){
    artworks.push({
      id:'Q'+(1000+i),
      title:`Opera Demo ${i}`,
      image:`https://picsum.photos/seed/opera${i}/400/300`,
      author: i%2? 'Autore A':'Autore B',
      meta:{ period:'XXI', origin:'Demo' }
    });
  }
  // items: generate couple of items per artwork
  const items = [];
  let idc=1;
  artworks.forEach((a,idx)=>{
    const baseId = 'item'+idc++;
    items.push({
      id: baseId,
      objectId: a.id,
      title: a.title + ' - descrizione breve',
      author: 'autore1',
      license: 'CC-BY',
      price: idx%3===0? 2.5:0,
      duration: 15,
      image: a.image,
      tone: ['infantile','semplice','medio','avanzato'][idx%4],
      texts: { t3:`${a.title} (3s)`, t15:`${a.title} (15s) - breve descrizione`, t40:`${a.title} (40s) - testo esteso`},
      published: true
    });
  });
  // visits
  const visits = [
    { id:'visit1', museumId:museum.id, title:'Visita Base - 10 opere', owner:'autore1', items: items.map(it=>({itemId:it.id, optional:false})) },
    { id:'visit2', museumId:museum.id, title:'Visita Avanzata', owner:'autore2', items: items.slice(0,6).map(it=>({itemId:it.id, optional:false})) },
    { id:'visit3', museumId:museum.id, title:'Visita Scolastica', owner:'autore1', items: items.slice(2,9).map(it=>({itemId:it.id, optional:false})) }
  ];
  const users = DEFAULT_USERS;
  db = { museums:[museum], artworks, items, visits, users, sessions:[] };
  localStorage.setItem(STORAGE_KEY, JSON.stringify(db));
  return db;
}
function saveDB(){ localStorage.setItem(STORAGE_KEY, JSON.stringify(db)); }

// ---------- Init ----------
function init(){
  db = loadDB();
  populateUsers();
  populateMuseums();
  populateItems();
  populateVisits();
  hookEvents();
  updateSessionUI();
}

function populateUsers(){
  userSelect.innerHTML = '';
  db.users.forEach(u=>{
    const opt = document.createElement('option');
    opt.value=u.id; opt.textContent = `${u.id} (${u.role})`;
    userSelect.appendChild(opt);
  });
  // auto-login first user
  currentUser = db.users[0];
  userSelect.value = currentUser.id;
  userSelect.addEventListener('change', ()=> {
    currentUser = db.users.find(x=>x.id===userSelect.value);
    renderAll();
  });
  logoutBtn.addEventListener('click', ()=> { alert('Questo prototipo non ha logout server-side.'); });
}

function populateMuseums(){
  museumSelect.innerHTML = '';
  db.museums.forEach(m=>{
    const o=document.createElement('option'); o.value=m.id; o.textContent=m.title; museumSelect.appendChild(o);
  });
  museumSelect.addEventListener('change', renderAll);
}

function populateItems(){
  renderItems();
}

function renderItems(){
  const museumId = museumSelect.value || db.museums[0].id;
  const q = searchInput.value.toLowerCase();
  const tone = filterTone.value;
  itemsList.innerHTML='';
  const visible = db.items.filter(it=>{
    if(tone && it.tone !== tone) return false;
    if(q && !(it.title.toLowerCase().includes(q) || it.texts.t15.toLowerCase().includes(q))) return false;
    return true;
  });
  visible.forEach(it=>{
    const card = document.createElement('div'); card.className='itemCard';
    card.innerHTML = `<img src="${it.image}" alt=""><div style="flex:1">
      <strong>${it.title}</strong>
      <div class="muted">${it.author} • ${it.license} • €${it.price}</div>
      <div style="margin-top:6px"><button data-id="${it.id}" class="editBtn">Edit</button>
      <button data-id="${it.id}" class="publishToggle">${it.published? 'Unpubblica':'Pubblica'}</button>
      </div></div>`;
    itemsList.appendChild(card);
  });
  // attach
  document.querySelectorAll('.editBtn').forEach(b=>b.addEventListener('click', e=>{
    const id = e.target.dataset.id; openEditor(id);
  }));
  document.querySelectorAll('.publishToggle').forEach(b=>b.addEventListener('click', e=>{
    const id=e.target.dataset.id; const it = db.items.find(x=>x.id===id); it.published = !it.published; saveDB(); renderItems();
  }));
}

function renderVisits(){
  visitsList.innerHTML='';
  db.visits.forEach(v=>{
    const node = document.createElement('div'); node.className='itemCard';
    node.innerHTML = `<div style="flex:1"><strong>${v.title}</strong><div class="muted">owner: ${v.owner}</div>
      <div style="margin-top:6px"><button data-id="${v.id}" class="editVisit">Modifica</button>
      <button data-id="${v.id}" class="publishVisit">Apri in Navigator</button></div></div>`;
    visitsList.appendChild(node);
  });
  document.querySelectorAll('.editVisit').forEach(b=>b.addEventListener('click', e=>{
    editVisit(e.target.dataset.id);
  }));
  document.querySelectorAll('.publishVisit').forEach(b=>b.addEventListener('click', e=>{
    alert('Integrazione: salvata per Navigator. (In app reale inviare API)');
  }));
}

function populateVisits(){
  const sel = syncVisitSelect;
  sel.innerHTML = '';
  db.visits.forEach(v=> {
    const opt = document.createElement('option'); opt.value=v.id; opt.textContent=v.title; sel.appendChild(opt);
  });
  renderVisits();
}

function hookEvents(){
  searchInput.addEventListener('input', renderItems);
  filterTone.addEventListener('change', renderItems);
  newItemBtn.addEventListener('click', ()=> openEditor());
  cancelEditBtn.addEventListener('click', ()=> { editorPanel.classList.add('hidden'); });
  itemForm.addEventListener('submit', onSaveItem);
  publishBtn.addEventListener('click', onPublishItem);
  newVisitBtn.addEventListener('click', createVisit);
  startSessionBtn.addEventListener('click', startSession);
  stopSessionBtn.addEventListener('click', stopSession);
}

function openEditor(itemId){
  editorPanel.classList.remove('hidden');
  if(itemId){
    editingItemId = itemId;
    const it = db.items.find(x=>x.id===itemId);
    fObjectId.value = it.objectId; fTitle.value = it.title; fAuthor.value = it.author; fLicense.value = it.license;
    fPrice.value = it.price; fDuration.value = it.duration; fImage.value = it.image; fTone.value = it.tone;
    f3.value = it.texts.t3; f15.value = it.texts.t15; f40.value = it.texts.t40;
  } else {
    editingItemId = null;
    itemForm.reset();
  }
}

function onSaveItem(e){
  e.preventDefault();
  const payload = {
    id: editingItemId || ('item'+(Date.now()%100000)),
    objectId: fObjectId.value,
    title: fTitle.value,
    author: fAuthor.value || currentUser.id,
    license: fLicense.value || 'CC-BY',
    price: parseFloat(fPrice.value||0),
    duration: parseInt(fDuration.value||15),
    image: fImage.value||'https://picsum.photos/200/160',
    tone: fTone.value,
    texts: { t3:f3.value, t15:f15.value, t40:f40.value },
    published: false
  };
  if(editingItemId){
    const idx = db.items.findIndex(x=>x.id===editingItemId); db.items[idx] = payload;
  } else {
    db.items.push(payload);
  }
  saveDB(); renderItems(); editorPanel.classList.add('hidden'); populateVisits();
}

function onPublishItem(){
  if(!editingItemId) alert('Devi prima salvare l\'item');
  else {
    const it = db.items.find(x=>x.id===editingItemId);
    it.published = true; saveDB(); renderItems(); alert('Item pubblicato');
  }
}

function createVisit(){
  const id = 'visit'+Date.now()%100000;
  const title = prompt('Nome visita:','Nuova Visita');
  if(!title) return;
  // simple: include first 5 published items
  const items = db.items.slice(0,5).map(i=>({itemId:i.id, optional:false}));
  db.visits.push({ id, museumId: db.museums[0].id, title, owner: currentUser.id, items});
  saveDB(); populateVisits();
}

function editVisit(visitId){
  const v = db.visits.find(x=>x.id===visitId);
  const newTitle = prompt('Titolo visita:', v.title);
  if(newTitle){ v.title = newTitle; saveDB(); populateVisits(); }
}

// ---------- Session simulation (synchronized visit) ----------
function startSession(){
  const visitId = syncVisitSelect.value;
  const code = sessionCode.value.trim() || ('S'+Math.floor(Math.random()*9000+1000));
  if(!visitId){ alert('Seleziona una visita'); return; }
  activeSession = { code, visitId, startedAt: Date.now(), connections:[], log:[] };
  db.sessions.push(activeSession); saveDB();
  startSessionBtn.disabled = true; stopSessionBtn.disabled = false;
  sessionLog.innerHTML = `Sessione ${code} avviata per visita ${visitId}`;
  updateSessionUI();
}
function stopSession(){
  if(!activeSession) return;
  activeSession = null;
  startSessionBtn.disabled = false; stopSessionBtn.disabled = true;
  sessionLog.innerHTML += '\nSessione fermata';
  updateSessionUI();
}
function updateSessionUI(){
  studentCount.textContent = activeSession? activeSession.connections.length : 0;
}

// ---------- simple render / run ----------
function renderAll(){ renderItems(); renderVisits(); updateSessionUI(); }
init();
