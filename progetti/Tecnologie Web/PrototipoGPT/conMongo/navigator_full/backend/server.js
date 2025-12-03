/**
 * Simple Express + Mongoose backend implementing required collections:
 * Users, Museums, Items, Visits, Sessions, Quizzes
 * Note: This is a straightforward implementation intended for local development.
 */

const express = require('express');
const mongoose = require('mongoose');
const morgan = require('morgan');
const cors = require('cors');
const app = express();
require('dotenv').config();

const MONGO = process.env.MONGO_URI || 'mongodb://127.0.0.1:27017/artaround_demo';
const PORT = process.env.PORT || 3000;

app.use(morgan('dev'));
app.use(cors());
app.use(express.json());

// models
const User = require('./models/user');
const Museum = require('./models/museum');
const Item = require('./models/item');
const Visit = require('./models/visit');
const Session = require('./models/session');

// connect
mongoose.connect(MONGO, { useNewUrlParser: true, useUnifiedTopology: true })
  .then(()=> console.log('Connected to MongoDB'))
  .catch(err=> { console.error('Mongo error', err); process.exit(1); });

// simple health
app.get('/health', (req,res)=> res.json({ok:true}));

// auth-lite endpoints (for prototyping)
app.get('/api/users', async (req,res)=> {
  const users = await User.find({}, '-pwd');
  res.json(users);
});
app.post('/api/login', async (req,res)=> {
  const {id, pwd} = req.body;
  const u = await User.findOne({id});
  if(!u) return res.status(401).json({error:'invalid_user'});
  if(u.pwd !== pwd) return res.status(401).json({error:'invalid_pwd'});
  res.json({id:u.id, role:u.role});
});

// museums
app.get('/api/museums', async (req,res)=> {
  const m = await Museum.find();
  res.json(m);
});
app.post('/api/museums', async (req,res)=> {
  const m = new Museum(req.body);
  await m.save();
  res.json(m);
});

// items
app.get('/api/items', async (req,res)=> {
  const items = await Item.find();
  res.json(items);
});
app.get('/api/items/:id', async (req,res)=> {
  const it = await Item.findById(req.params.id);
  if(!it) return res.status(404).end();
  res.json(it);
});
app.post('/api/items', async (req,res)=> {
  const it = new Item(req.body);
  await it.save();
  res.json(it);
});
app.put('/api/items/:id', async (req,res)=> {
  const it = await Item.findByIdAndUpdate(req.params.id, req.body, {new:true});
  res.json(it);
});

// visits
app.get('/api/visits', async (req,res)=> {
  const visits = await Visit.find().populate('items.itemId').exec();
  res.json(visits);
});
app.post('/api/visits', async (req,res)=> {
  const v = new Visit(req.body);
  await v.save();
  res.json(v);
});

// sessions (synchronized visits)
app.get('/api/sessions', async (req,res)=> {
  const s = await Session.find();
  res.json(s);
});
app.post('/api/sessions', async (req,res)=> {
  const s = new Session(req.body);
  await s.save();
  res.json(s);
});
app.put('/api/sessions/:id', async (req,res)=> {
  const s = await Session.findByIdAndUpdate(req.params.id, req.body, {new:true});
  res.json(s);
});

app.listen(PORT, ()=> console.log('Server listening on', PORT));
