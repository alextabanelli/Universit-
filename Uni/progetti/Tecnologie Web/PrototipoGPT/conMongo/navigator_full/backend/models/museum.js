const mongoose = require('mongoose');
const Schema = mongoose.Schema;
const MuseumSchema = new Schema({
  id: {type:String, unique:true},
  title: String,
  cover: String,
  desc: String,
  config: Schema.Types.Mixed
});
module.exports = mongoose.model('Museum', MuseumSchema);
