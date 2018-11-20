exports.who = async (bot, message, args, userData) => {

  var fs = require('fs');
  // var userData = JSON.parse(fs.readFileSync('Storage/userData.json', 'utf8'));
  var config = JSON.parse(fs.readFileSync('Storage/config.json', 'utf8'));
  var sender = message.author;

  let luck = 0;
  let a = '';



  function ungodlyLuck()
  {
    userdata[265957683260030976].whosCollected += userData[sender.id].whosCollected /2;
    userdata[sender.id].whosCollected = userData[sender.id].whosCollected / 2;
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: 'WHO? Lottery!',
      description: '<(O_o)> WHO? really didn\'t like ' + sender.username + ' and WHO? took half their WHO?\'s... FeelsBadMan'
    }});
  }
  function terribleLuck()
  {
    luck = Math.ceil(Math.random() * 3);
    switch (luck)
    {
      case 1:
        a = ('*You have luck that not even a worm would show pity upon.*');
        break;
      case 2:
        a = ('*Did you somehow anger WHO??*');
        break;
      default:
        a = ('*Come back another day... or maybe not.*');
        break;
    }
    userData[sender.id].whosCollected -= 5;
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: 'WHO? Lottery!',
      description: sender.username + ' lost 5 WHO?\'s\n' + a
    }});
  }
  function badLuck()
  {
    luck = Math.ceil(Math.random() * 3);
    switch (luck)
    {
      case 1:
        a = ('*Maybe try again.*');
        break;
      case 2:
        a = ('*How about you return but with better intensions.*');
        break;
      default:
        a = ('*What happened here? Did you make a mistake?*');
        break;
    }
    userData[sender.id].whosCollected--;
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: 'WHO? Lottery!',
      description: sender.username + ' lost 1 WHO?\n' + a
    }});
  }
  function averageLuck()
  {
    luck = Math.ceil(Math.random() * 3);
    switch (luck)
    {
      case 1:
        a = ('*Not bad for a pleb.*');
        break;
      case 2:
        a = ('*That was almost great. Keep trying.*');
        break;
      default:
        a = ('*Try a little harder.*');
        break;
    }
    userData[sender.id].whosCollected++;
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: 'WHO? Lottery!',
      description: sender.username + ' gained 1 WHO?\n' + a
    }});
  }
  function goodLuck()
  {
    luck = Math.ceil(Math.random() * 3);
    switch (luck)
    {
      case 1:
        a = ('*You could make a living from this.*');
        break;
      case 2:
        a = ('*That was a good offer.*');
        break;
      default:
        a = ('*That was above average.*');
        break;
    }
    userData[sender.id].whosCollected += 5;
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: 'WHO? Lottery!',
      description: sender.username + ' got lucky and gained 5 WHO?\'s\n' + a
    }});
  }
  function godlyLuck()
  {
    userData[sender.id].whosCollected += 1000000;
    message.channel.send({embed:{
      author: {
        name: sender.username,
        icon_url: sender.avatarURL
      },
      title: 'WHO? Lottery!',
      description: '**<(OvO)> ' + sender.username + ' just got WHO?\'s approval and gained the jackpot of __1000000__ WHO?\'s! <(OvO)>**'
    }});
    console.log(sender.username + ' just got a JACKPOT!');
  }

  let chance = Math.ceil(Math.random() * 100);

  if (!userData[sender.id]) userData[sender.id] = {
    userName: sender.username,
    whosCollected: 0
  }
  if (chance >= 99)
  {
    if (chance >= 99)
    {
      godlyLuck();
    }
    else if (chance >= 80 && chance < 99)
    {
      goodLuck();
    }
    else if (chance >= 50 && chance < 80)
    {
      averageLuck();
    }
    else if (chance >= 10 && chance < 50)
    {
      badLuck();
    }
    else if (chance >= 5 && chance < 10)
    {
      terribleLuck();
    }
    else if (chance < 5)
    {
      ungodlyLuck();
    }
  }
  else if (chance >= 80 && chance < 99)
  {
    goodLuck();
  }
  else if (chance >= 50 && chance < 80)
  {
    averageLuck();
  }
  else if (chance >= 10 && chance < 50)
  {
    badLuck();
  }
  else if (chance >= 5 && chance < 10)
  {
    terribleLuck();
  }
  else if (chance < 5)
  {
    ungodlyLuck();
  }
  else
  {
    message.send('Something went wrong...');
  }
  console.log(sender.username + ' just rolled a ' + chance);

  fs.writeFile('./Storage/userData.json', JSON.stringify(userData, null, 2), (err) =>{
    if (err) console.error(err);
  });
}
