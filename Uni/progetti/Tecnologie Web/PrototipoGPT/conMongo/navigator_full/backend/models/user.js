const mongoose = require('mongoose');
const Schema = mongoose.Schema;
const UserSchema = new Schema({
  id: {type:String, unique:true},
  role: {type:String, enum:['author','visitor','admin'], default:'visitor'},
  pwd: {type:String}
});
module.exports = mongoose.model('User', UserSchema);
