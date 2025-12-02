const mongoose = require('mongoose');
const Schema = mongoose.Schema;
const ItemSchema = new Schema({
  objectId: String,
  title: String,
  author: String,
  license: String,
  price: Number,
  duration: Number,
  image: String,
  tone: String,
  texts: Schema.Types.Mixed,
  published: {type:Boolean, default:false}
});
module.exports = mongoose.model('Item', ItemSchema);
