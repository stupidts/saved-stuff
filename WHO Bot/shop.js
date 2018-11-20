function setup (bot, message){
  var fs = require('fs');
  var userData = JSON.parse(fs.readFileSync('Storage/userData.json', 'utf8'));
  var shops = JSON.parse(fs.readFileSync('Storage/Shops/shops.json', 'utf8'));
  var sender = message.author;
  if (!userData[sender.id]) userData[sender.id] = {
    userName: sender.user.username,
    whosCollected: 0
  }
  if (!userData[sender.id].weapon) userData[sender.id].weapon = 'Unarmed';
  if (!userData[sender.id].armor) userData[sender.id].armor = 'No Armor';
  if (!userData[sender.id].weaponValue) userData[sender.id].weaponValue = 0;
  if (!userData[sender.id].armorValue) userData[sender.id].armorValue = 0;
  fs.writeFile('Storage/userData.json', JSON.stringify(userData, null, 2), (err) => {
    if (err) console.error(err);
  });
  return shops;
}
function hooksetup (bot) {
  var hooks = require('./hooks.js');
  return hooks;
}
function FS() {
  var fs = require('fs');
}

exports.list = async (bot, message, args) => {
  var shops = setup(bot, message);
  var hooks = hooksetup(bot);
  var fs = require('fs');
  //makes the file not null
  if (!shops[1]) {
    shops = {shopsLength:1}
    shops[1] = {
    shopName: 'WHO?\'s Shop',
    shopDescription: 'WHO?\'s Shop is for everyone to use. Get awesome gear, cool weapons, and more!',
    shopOwner: 265957683260030976,
    shopClub: 'none',
    shopRole: 'everyone'
    }
    fs.writeFile('Storage/Shops/shops.json', JSON.stringify(shops, null, 2), (err) => {
      if (err) {console.error(err);} //else {console.log('set shops');}
    });
  }

  // console.log(shops + ', ' + shopsList);
  var shopsLength = shopsLength;
  // console.log(shops.shopsLength, shops[1].shopName);

  var shopsList = ' ';
  for (var i = 1; i <= shops.shopsLength; i++) {
    // console.log(`Shops List: ${i}`)
    shopsList += `${shops[i].shopName} - ${shops[i].shopDescription}\n`;
  }
  // console.log('shopsList: ', shopsList);
  hooks.hooks(message.channel, 'Shops!', shopsList, '696969', 'https://cdn.discordapp.com/attachments/420745531896365066/475515246421868576/WHOLottery.png');
}
