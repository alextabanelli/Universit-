const mongoose = require('mongoose');
const Schema = mongoose.Schema;
const SessionSchema = new Schema({
  code: {type:String, index:true},
  visitId: {type: Schema.Types.ObjectId, ref:'Visit'},
  startedAt: Date,
  connections: [Schema.Types.Mixed],
  log: [Schema.Types.Mixed]
});
module.exports = mongoose.model('Session', SessionSchema);
