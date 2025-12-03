const mongoose = require('mongoose');
const Schema = mongoose.Schema;
const VisitSchema = new Schema({
  museumId: {type:String, index:true},
  title: String,
  owner: String,
  items: [{ itemId: {type: Schema.Types.ObjectId, ref:'Item'}, optional:Boolean }]
});
module.exports = mongoose.model('Visit', VisitSchema);
