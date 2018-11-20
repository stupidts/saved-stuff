module.exports.run = async (bot, message, args, userData) => {

  var fs = require('fs');
  // var userData = JSON.parse(fs.readFileSync('Storage/userData.json', 'utf8'));
  var sender = message.author;


  if (!userData[sender.id]) userData[sender.id] = {
    userName: sender.username,
    whosCollected: 0,
    weapon: 'Unarmed',
    armor: 'No Armor',
    weaponValue: 0,
    armorValue: 0
  }
  fs.writeFile('Storage/userData.json', JSON.stringify(userData, null, 2), (err) => {
    if (err) console.error(err);
  });
  //hooks.hookstats(message.channel, sender.username, ('Username: ' + sender.username + ' \nWHO?\'s collected: ' + userData[sender.id].whosCollected + ' \nWeapon: ' + userData[sender.id].weapon + ' \nArmor: ' + userData[sender.id].armor), '696969', 'https://cdn.discordapp.com/attachments/420745531896365066/475515252943880202/WHOStats.png');
  //hook(message.channel, sender.username, ('Username: ' + sender.username + ' \nWHO?\'s collected: ' + userData[sender.id].whosCollected + ' \nWeapon: ' + userData[sender.id].weapon + ' \nArmor: ' + userData[sender.id].armor), '696969', 'https://cdn.discordapp.com/attachments/420745531896365066/475515252943880202/WHOStats.png');
  /*message.channel.send({embed:{
    author: {
      name: sender.username,
      icon_url: sender.avatarURL
    },
    title: 'Stats',
    description: 'Username: ' + sender.username + ' \nWHO?\'s collected: ' + userData[sender.id].whosCollected +
    ' \nWeapon: ' + userData[sender.id].weapon + ' \nArmor: ' + userData[sender.id].armor,
  }})*/

}

module.exports.config = {
  command: "statss"
}
