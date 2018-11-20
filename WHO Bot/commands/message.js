module.exports.run = async (bot, message, args, userData) => {

  var fs = require('fs');
  // var userData = JSON.parse(fs.readFileSync('Storage/userData.json', 'utf8'));
  var enemies = JSON.parse(fs.readFileSync('Storage/enemies.json', 'utf8'));
  let sender = message.author;

}

module.exports.config = {
  command: '{-}'
}
