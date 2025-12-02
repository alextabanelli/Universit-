ArtAround - Backend (Node.js + Express + MongoDB)
---------------------------------------------------

Files:
- server.js            (main Express server)
- models/*.js          (mongoose models: user, museum, item, visit, session)
- seed.js              (script to populate demo data)
- package.json

Quick start:
1. Install dependencies:
   npm install

2. Configure environment:
   Create a .env file with:
     MONGO_URI=mongodb://127.0.0.1:27017/artaround_demo
     PORT=3000

3. Seed the DB:
   npm run seed

4. Start the server:
   npm start

API highlights:
- GET /api/museums
- GET /api/items
- POST /api/items
- GET /api/visits
- POST /api/visits
- GET /api/sessions
- POST /api/sessions

This backend is a starting point for the ArtAround Marketplace & Navigator projects.
