/**
 * Seed script to populate MongoDB with demo data.
 * Run: node seed.js (ensure MONGO_URI env var or default localhost)
 */
const mongoose = require('mongoose');
require('dotenv').config();
const User = require('./models/user');
const Museum = require('./models/museum');
const Item = require('./models/item');
const Visit = require('./models/visit');
const Session = require('./models/session');

const MONGO = process.env.MONGO_URI || 'mongodb://127.0.0.1:27017/artaround_demo';

async function seed(){
  await mongoose.connect(MONGO, {useNewUrlParser:true, useUnifiedTopology:true});
  console.log('Connected to', MONGO);
  await Promise.all([User.deleteMany({}), Museum.deleteMany({}), Item.deleteMany({}), Visit.deleteMany({}), Session.deleteMany({})]);

  const users = [
    {id:'autore1', role:'author', pwd:'12345678'},
    {id:'autore2', role:'author', pwd:'12345678'},
    {id:'visitatore1', role:'visitor', pwd:'12345678'},
    {id:'visitatore2', role:'visitor', pwd:'12345678'}
  ];
  await User.insertMany(users);
  const museum = { id:'mambo', title:'Pinacoteca Demo', cover:'https://picsum.photos/seed/museo/800/300', desc:'Museo demo' };
  const m = await Museum.create(museum);

  const items = [];
  for(let i=1;i<=10;i++){
    const item = await Item.create({
      objectId: 'Q'+(1000+i),
      title: `Opera Demo ${i}`,
      author: i%2? 'Autore A':'Autore B',
      license: 'CC-BY',
      price: i%3===0? 2.5:0,
      duration: 15,
      image: `https://picsum.photos/seed/opera${i}/400/300`,
      tone: ['infantile','semplice','medio','avanzato'][i%4],
      texts: { t3:`Opera Demo ${i} (3s)`, t15:`Opera Demo ${i} (15s)`, t40:`Opera Demo ${i} (40s)` },
      published: true
    });
    items.push(item);
  }

  const visits = [
    { museumId: m.id, title:'Visita Base - 10 opere', owner:'autore1', items: items.map(it=>({itemId:it._id, optional:false})) },
    { museumId: m.id, title:'Visita Avanzata', owner:'autore2', items: items.slice(0,6).map(it=>({itemId:it._id, optional:false})) },
    { museumId: m.id, title:'Visita Scolastica', owner:'autore1', items: items.slice(2,9).map(it=>({itemId:it._id, optional:false})) }
  ];
  const v = await Visit.insertMany(visits);

  const session = await Session.create({ code:'FeniceRossa', visitId:v[0]._id, startedAt: new Date(), connections:[], log:[] });

  console.log('Seed complete');
  process.exit(0);
}

seed().catch(err=>{ console.error(err); process.exit(1); });
