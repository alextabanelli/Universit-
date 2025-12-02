// Navigator mock (no backend). Loads same localStorage seed used by marketplace mock (STORAGE_KEY must match).
const STORAGE_KEY = 'artaround_db_v1';
const navUserSelect = document.getElementById('navUserSelect');
const visitListNav = document.getElementById('visitListNav');
const visitTitle = document.getElementById('visitTitle');
const player = document.getElementById('player');
const ciImg = document.getElementById('ciImg');
const ciTitle = document.getElementById('ciTitle');
const ciMeta = document.getElementById('ciMeta');
const ciText = document.getElementById('ciText');
const btnNext = document.getElementById('btnNext');
const btnPrev = document.getElementById('btnPrev');
const btnMore = document.getElementById('btnMore');
const btnLess = document.getElementById('btnLess');
const btnSimple = document.getElementById('btnSimple');
const btnHard = document.getElementById('btnHard');
const btnPlay = document.getElementById('btnPlay');
const joinSessionBtn = document.getElementById('joinSessionBtn');
const joinCode = document.getElementById('joinCode');
const quizArea = document.getElementById('quizArea');
const quizContainer = document.getElementById('quizContainer');

let db = null;
let currentUser = null;
let currentVisit = null;
let currentIndex = 0;
let playbackTone = 'medio'; // default tone preference
let joinedSession = null;

function loadDB(){
  const raw = localStorage.getItem(STORAGE_KEY);
  if(!raw){ alert('Nessuna DB seed trovato. Apri prima il Marketplace mock per popolare il localStorage.'); return null; }
  return JSON.parse(raw);
}
function populateUsers(){
  db.users.forEach(u=>{
    const opt=document.createElement('option'); opt.value=u.id; opt.textContent=u.id; navUserSelect.appendChild(opt);
  });
  navUserSelect.addEventListener('change', ()=> currentUser = db.users.find(x=>x.id===navUserSelect.value));
  currentUser = db.users[0]; navUserSelect.value = currentUser.id;
}

function renderVisitsList(){
  visitListNav.innerHTML='';
  db.visits.forEach(v=>{
    const btn = document.createElement('button'); btn.textContent = v.title; btn.addEventListener('click', ()=> openVisit(v.id));
    visitListNav.appendChild(btn);
  });
}

function openVisit(visitId){
  currentVisit = db.visits.find(v=>v.id===visitId);
  if(!currentVisit) return;
  visitTitle.textContent = currentVisit.title;
  currentIndex = 0;
  player.classList.remove('hidden');
  renderCurrentItem();
}

function renderCurrentItem(){
  if(!currentVisit) return;
  const current = currentVisit.items[currentIndex];
  const item = db.items.find(x=>x.id===current.itemId);
  ciImg.src = item.image;
  ciTitle.textContent = item.title;
  ciMeta.textContent = `${item.author} • ${item.license} • durata: ${item.duration}s • tono: ${item.tone}`;
  // choose text by playbackTone preference: prefer matching tone, else fallback t15
  const selectedText = pickVariantText(item);
  ciText.textContent = selectedText;
  // quiz area toggler: show only if visit has a quiz stored (in prototipo not implemented), kept for future integration
  quizArea.classList.add('hidden');
}

function pickVariantText(item){
  // prefer t15, but if user asked more/less or tone change we may pick t3 or t40
  if(playbackTone==='infantile' && item.tone==='infantile') return item.texts.t15;
  // default: return t15
  return item.texts.t15 || item.texts.t3;
}

// voice controls (vocabolo controllato)
btnNext.addEventListener('click', ()=> {
  if(joinedSession && joinedSession.controlled) { alert('Sessione sincronizzata: non puoi andare avanti'); return; }
  if(currentVisit && currentIndex < currentVisit.items.length-1){ currentIndex++; renderCurrentItem(); }
});
btnPrev.addEventListener('click', ()=> {
  if(joinedSession && joinedSession.controlled) { alert('Sessione sincronizzata: non puoi tornare indietro'); return; }
  if(currentVisit && currentIndex > 0){ currentIndex--; renderCurrentItem(); }
});
btnMore.addEventListener('click', ()=> { // dimmi di più -> show t40 if present
  const item = db.items.find(x=>x.id===currentVisit.items[currentIndex].itemId);
  ciText.textContent = item.texts.t40 || item.texts.t15;
});
btnLess.addEventListener('click', ()=> {
  const item = db.items.find(x=>x.id===currentVisit.items[currentIndex].itemId);
  ciText.textContent = item.texts.t3 || item.texts.t15;
});
btnSimple.addEventListener('click', ()=> {
  playbackTone = 'semplice';
  // attempt to find item variant with tone 'semplice'
  const item = db.items.find(x=>x.id===currentVisit.items[currentIndex].itemId);
  if(item.tone==='semplice') ciText.textContent = item.texts.t15;
  else ciText.textContent = item.texts.t15 + ' (versione semplificata non disponibile)';
});
btnHard.addEventListener('click', ()=> {
  playbackTone = 'avanzato';
  const item = db.items.find(x=>x.id===currentVisit.items[currentIndex].itemId);
  if(item.tone==='avanzato') ciText.textContent = item.texts.t40;
  else ciText.textContent = item.texts.t15 + ' (versione avanzata non disponibile)';
});

btnPlay.addEventListener('click', ()=>{
  const text = ciText.textContent;
  if(!('speechSynthesis' in window)){ alert('TTS non disponibile in questo browser'); return; }
  const u = new SpeechSynthesisUtterance(text);
  speechSynthesis.speak(u);
});

// Join session (simulated): if exists in db.sessions with matching code, we join as student.
joinSessionBtn.addEventListener('click', ()=>{
  const code = joinCode.value.trim();
  if(!code) return alert('Inserisci codice');
  const session = db.sessions && db.sessions.find(s=>s.code===code);
  if(!session) return alert('Sessione non trovata nel DB (usa il Marketplace per avviarla)');
  joinedSession = { code: session.code, visitId: session.visitId, controlled: true };
  // register connection
  if(!session.connections) session.connections=[];
  session.connections.push({user: currentUser.id, at: Date.now()});
  localStorage.setItem(STORAGE_KEY, JSON.stringify(db));
  // load visit and lock controls
  openVisit(session.visitId);
  alert('Connesso come studente. I comandi prossimo/precedente sono disattivati.');
});

// For offline demo: allow teacher to act by starting session in marketplace; Navigator just reads local DB for sessions.
function init(){
  db = loadDB();
  if(!db) return;
  populateUsers();
  renderVisitsList();
}
init();
