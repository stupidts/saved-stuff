module.exports.run = async (bot, message, args, userData) => {

  var fs = require('fs');
  // var userData = JSON.parse(fs.readFileSync('Storage/userData.json', 'utf8'));
  var enemies = JSON.parse(fs.readFileSync('Storage/enemies.json', 'utf8'));
  let sender = message.author;

  if (!userData[sender.id].isUser) userData[sender.id].isUser = 1;
  let enemyDamage = 10;
  let randomNumber = 0;
  let critChance = 10; //higher is worse chance| if it's 10 then there's a 10% chance. If it's 100 then there's a 1% chance. If it's 1 then there's a 100% chance.

  // console.log(args[0]);
  if (args[0] == null)
  {
    message.channel.send ({embed:{
      author: {
        name: sender.username,
        icon_url: message.author.avatarURL
      },
      title: 'Fighting Enemies.',
      description: 'Please enter a value from 1 to 10. 1 Being the easiest difficulty, 10 Being the hardest difficulty. \nOr challenge a player by typing their username.'
    }});
    return;
  }
  else if (args[0].startsWith('@'))
  {
    if (args[0].isUser == null) return;
    else
    {
      playerVplayer();
    }
  }
  else
  {
    switch (args[0])
    {
      case '1':
        level1();
        break;
      case '2':
        level2();
        break;
      case '3':
        level3();
        break;
      case '4':
        level4();
        break;
      case '5':
        level5();
        break;
      case '6':
        level6();
        break;
      case '7':
        level7();
        break;
      case '8':
        level8();
        break;
      case '9':
        level9();
        break;
      case '10':
        level10();
        break;
      case '1337':
        levelUnknown();
        break;
      default:
        message.channel.send ({embed:{
          title: 'Fighting Enemies.',
          description: 'Please enter a value from 1 to 10. 1 Being the easiest difficulty, 10 Being the hardest difficulty.'
        }});
        break;
    }
  }

  function playerVplayer ()
  {
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: '**Player Vs Player**',
      description: sender.username + ' challenged ' + args[0]
    }});
  }
  function level1()
  {
    randomNumber = Math.floor(Math.random() * 5);
    console.log(sender.username + ' ' + sender.id + ', Random number = ' + randomNumber + ', ' + enemies.level1[randomNumber]);
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: '**Level 1 Fight!**',
      description: sender.username + ' encountered a wild ' + enemies.level1[randomNumber]
    }});
  }
  function level2()
  {
    randomNumber = Math.floor(Math.random() * 5);
    console.log(sender.username + ' ' + sender.id + ', Random number = ' + randomNumber + ', ' + enemies.level2[randomNumber]);
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: '**Level 2 Fight!**',
      description: sender.username + ' encountered a wild ' + enemies.level2[randomNumber]
    }});
  }
  function level3()
  {
    randomNumber = Math.floor(Math.random() * 5);
    console.log(sender.username + ' ' + sender.id + ', Random number = ' + randomNumber + ', ' + enemies.level3[randomNumber]);
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: '**Level 3 Fight!**',
      description: sender.username + ' encountered a wild ' + enemies.level3[randomNumber]
    }});
  }
  function level4()
  {
    randomNumber = Math.floor(Math.random() * 4);
    console.log(sender.username + ' ' + sender.id + ', Random number = ' + randomNumber + ', ' + enemies.level4[randomNumber]);
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: '**Level 4 Fight!**',
      description: sender.username + ' encountered a wild ' + enemies.level4[randomNumber]
    }});
  }
  function level5()
  {
    randomNumber = Math.floor(Math.random() * 4);
    console.log(sender.username + ' ' + sender.id + ', Random number = ' + randomNumber + ', ' + enemies.level5[randomNumber]);
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: '**Level 5 Fight!**',
      description: sender.username + ' encountered a wild ' + enemies.level5[randomNumber]
    }});
  }
  function level6()
  {
    randomNumber = Math.floor(Math.random() * 3);
    console.log(sender.username + ' ' + sender.id + ', Random number = ' + randomNumber + ', ' + enemies.level6[randomNumber]);
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: '**Level 6 Fight!**',
      description: sender.username + ' encountered a wild ' + enemies.level6[randomNumber]
    }});
  }
  function level7()
  {
    randomNumber = Math.floor(Math.random() * 3);
    console.log(sender.username + ' ' + sender.id + ', Random number = ' + randomNumber + ', ' + enemies.level7[randomNumber]);
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: '**Level 7 Fight!**',
      description: sender.username + ' encountered a wild ' + enemies.level7[randomNumber]
    }});
  }
  function level8()
  {
    randomNumber = Math.floor(Math.random() * 3);
    console.log(sender.username + ' ' + sender.id + ', Random number = ' + randomNumber + ', ' + enemies.level8[randomNumber]);
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: '**Level 8 Fight!**',
      description: sender.username + ' encountered a wild ' + enemies.level8[randomNumber]
    }});
  }
  function level9()
  {
    randomNumber = Math.floor(Math.random() * 3);
    console.log(sender.username + ' ' + sender.id + ', Random number = ' + randomNumber + ', ' + enemies.level9[randomNumber]);
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: '**Level 9 Fight!**',
      description: sender.username + ' encountered a wild ' + enemies.level9[randomNumber]
    }});
  }
  function level10()
  {
    randomNumber = Math.floor(Math.random() * 2);
    console.log(sender.username + ' ' + sender.id + ', Random number = ' + randomNumber + ', ' + enemies.level10[randomNumber]);
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: '**Level 10 Fight!**',
      description: sender.username + ' encountered a wild ' + enemies.level10[randomNumber]
    }});
  }
  function levelUnknown()
  {
    if (sender.id !== '265957683260030976') return;
    randomNumber = Math.floor(Math.random() * 4);
    console.log(sender.username + ' ' + sender.id + ', Random number = ' + randomNumber + ', ' + enemies.levelUnknown[randomNumber]);
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: '**Level Unknown**',
      description: sender.username + ' encountered a wild ' + enemies.levelUnknown[randomNumber]
    }});
  }
}

module.exports.config = {
  command: 'fight'
}
