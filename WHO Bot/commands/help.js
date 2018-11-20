module.exports.run = async (bot, message, args, userData) => {

  var fs = require('fs');
  // var userData = JSON.parse(fs.readFileSync('Storage/userData.json', 'utf8'));
  let sender = message.author;

  if (!userData[sender.id]) userData[sender.id] =
  {
    userName: sender.user.username,
    whosCollected: 0
  }
  message.channel.send({embed:{
    author: {
      name: sender.username,
      icon_url: sender.avatarURL
    },
    title: 'Help',
    fields: [{
      name:'who',
      value: '*The \'who\' command will see through chance whether a user worthy for fortune.*'
    },
    {
      name: 'stats',
      value: '*The \'stats\' command shows a users stats.*'
    },
    {
      name: 'shop',
      value: '*The \'shop\' command allows a user to buy or sell items to improve your stats.*'
    },
    {
      name: 'fight',
      value: '*The \'fight\' command is used when a user wants to fight other users or enemies.*'
    },
    {
      name: 'lottome',
      value: '*The \'lottome\' command will give you access to use the WHO? lottery in the #who-lottery channel.*'
    }
    ]
  }});
}

module.exports.config = {
  command: "help"
}
