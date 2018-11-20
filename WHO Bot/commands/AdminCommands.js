module.exports.run = async (bot, message, args, userData) => {

  var fs = require('fs');
  //var userData = JSON.parse(fs.readFileSync('Storage/userData.json', 'utf8'));
  var config = JSON.parse(fs.readFileSync('Storage/config.json', 'utf8'));
  var fullMessage = message.content;
  let sender = message.author;

  // bot.fetchUser(user)
  // .then (user => {
  //   userName = user.username +'#'+ user.discriminator;
  //   console.log(user);
  // });

  function invalid(){console.log('!~~Invalid Command~~!');}

  if((message.author.id == '265957683260030976') && message.channel.type == 'dm')
  {
    if (args[0] == 'smessage' || args[0] == 'smsg')
    {
      if (isNaN(args[1]))
      {
        return message.channel.send('Please enter a valid user!');
      }
      else
      {
        if (args[2] != null)
        {
          // console.log(fullMessage);
          let msg = fullMessage.split('|')
          console.log(args[1]);
          let user = bot.fetchUser(args[1])
          .then(user => {
            user.send({embed:{
              author: {
                name: sender.username,
                icon_url: sender.avatarURL
              },
              fields: [
                {
                  name: 'You recieved a message!',
                  value: msg[1]
                }
              ]
            }});
            console.log(user.username + ' ' + user.id + ' has recieved a message from ' + message.author.username, + ' ' + message.author.id);
          });
        }
        else
        {
          message.channel.send('Please enter a message into the command. Message must start with |');
        }
      }
    }
    else if (args[0] == 'userinfo')
    {
      user = args[1];
      bot.fetchUser(user)
      .then (user => {
        console.log(user);
        user = user.toString();
        message.channel.send({embed:{
          title: 'Check console for info on:',
          description: user
        }});
      });
      console.log(user + ' userinfo found!');
    }
    else if (args[0] == 'config')
    {
      if (args[1] == null)
      {
        message.author.send({embed:{
          author: {
            name: sender.username,
            icon_url: sender.avatarURL
          },
          title: '**Config Commands**',
          fields: [{
            name: 'channel',
            value: '*Changes the channel that the bot will access*'
          },
          {
            name: 'who',
            value: '*Enables or disables the WHO? lottery*'
          }
        ],
        }})
      }
      else if (args[1].toLowerCase() == 'channel')
      {
        if (!isNaN(args[2]))
        {
          config.channelID = args[2];
          message.channel.send('WHO? Bot channel is now set to: ' + config.channelID);
          console.log(sender.username + ' ' + sender.id + ' changed WHO? Bots channel to ' + config.channelID);
          fs.writeFile('Storage/config.json', JSON.stringify(config), (err) =>{
            if (err) console.error(err);
          });
        }
        else if (args[2] == null)
        {
          message.channel.send('The current channel WHO? is assigned to is ' + config.channelID);
        }
        else
        {
          message.channel.send('The current channel WHO? is assigned to is ' + config.channelID);
        }
      }
      else if (args[1].toLowerCase() == 'who')
      {
        if (config.who == 1)
        {
          config.who = 0;
          message.channel.send('Turned WHO? lottery off.');
          console.log(sender.username + ' ' + sender.id + ' turned WHO? lottery OFF.');
        }
        else if (config.who == 0)
        {
          config.who = 1;
          message.channel.send('Turned WHO? lottery on.');
          console.log(sender.username + ' ' + sender.id + ' turned WHO? lottery ON.');
        }
        else
        {
          message.channel.send('\`who\` Something went wrong.');
        }
      }
      else
      {
        message.channel.send({embed:{
          author: {
            name: sender.username,
            icon_url: sender.avatarURL
          },
          title: '**Config Commands**',
          fields: [{
            name: 'channel',
            value: '*Changes the channel that the bot will access*'
          },
          {
            name: 'who',
            value: '*Toggles the WHO? lottery*'
          }
        ],
        }})
      }
    }
    else if (args[0] == 'stats')
    {
      var user = args[2];

      if (args[1] == 'list')
      {
        if (user !== null)
        {
          console.log('!~~Showing Stats~~!');
          console.log(message.author.username + ' is viewing ' + user + ', ' + user.username);

          message.channel.send({embed:{
            title: '\`\`\`!~~Stats~~!\`\`\`',
            description: 'User: ' + user + ', WHO?\'s Collected ' + userData[user].whosCollected
          }});
        }
        else {
          invalid();
        }
        console.log('!~~Showed Stats~~!');
      }
      else if (args[1] == 'edit')
      {
        if (args[2] == 'whos' && args[3] !== null)
        {
          userData[args[3]].whosCollected = args[4];
          console.log ('Edited ' + args[3] + '\'s stats.');
        }
      }
      else if (args[1] == 'add')
      {
        if (args[2] == whos && args[3] !== null)
        {
          userData[args[3]].whosCollected += args[4]
          console.log ('Edited ' + args[3] + '\s stats.');
        }
      }
      else
      {
        invalid();
      }
    }
    else if (args[0] == 'help')
    {
      message.channel.send({embed:{
        author: {
          name: sender.username,
          icon_url: sender.avatarURL
        },
        title: 'Admin Commands',
        fields: [
          {
            name: 'Message',
            value: '*Message is a way to send messages to a user through the bot without recieving any DM\'s back.*\n'+
            '\`!~~ msg\` *OR* \`!~~ message\` *followed by* \`userID\` *and a* \` | \`\n'+
            '*It is important to add the* | *after the userID so that the bot knows when the message starts.*\n'+
            '*Example:* \`!~~ msg 416436812182192148 | Hello there!\`'
          },
          {
            name: 'Secret Message',
            value: '*Secret Message is a way to send messages to a user through the bot without recieving any DM\'s back, and it also doesn\'t show who sent the message.*\n'+
            '\`!~~ smsg\` *OR* \`!~~ smessage\` *followed by* \`userID\` *and a* \` | \`\n'+
            '*It is important to add the* | *after the userID so that the bot knows when the message starts.*\n'+
            '*Example:* \`!~~ smsg 416436812182192148 | Hello there! (in secret :P)\`*'
          },
          {
            name: 'Stats',
            value: '*The stats command shows all the stats for a specific user.*\n'+
            '\`!~~ stats\` *followed by either* \`list\`, \`edit\`, *OR* \`add\`.\n'+
            '*__List__ shows all the stats for a user. __Edit__ will allow you to edit a users stats. __Add__ will allow you to add or subtract a value of a stat.*\n'+
            '*Example:* \`!~~ stats list 416436812182192148\`\n'+
            '*Example:* \`!~~ stats edit 416436812182192148 whosCollected 1000\`\n'+
            '*Example:* \`!~~ stats add 416436812182192148 whosCollected 500\`'

          },
          {
            name: 'Config',
            value: '*The config command will change certain config settings for the WHO? Bot.*\n'+
            '*The WHO? Lottery command will toggle the lottery on or off.*\n'+
            '*The channel command will allow the WHO? Bot\'s channel to be changed.*\n'+
            '*Example:* \`!~~ config who\`\n'+
            '*Example:* \`!~~ config channel 420724328544469045\`'
          }
        ]
      }});
      }
    else
    {
      invalid();
    }
    if(message.channel.type !== 'dm'){message.delete();}
  }
  else if (message.channel.type !== 'dm')
  {
    message.author.send({embed:{
      title: '\`\`\`!~~Introduction~~!\`\`\`',
      description: 'Please send Admin Commands to the WHO? Bot ONLY! \nTo begin try typing \`!~~ help\`.'
    }});
    console.log('Sent ' + message.author.username + ' an Introduction message.');
    message.delete();
  }
  else
  {
    message.delete();
    return console.log(message.author.id + ', ' + message.author.username+ ' tried to use Admin Commands!');
  }

  fs.writeFile('Storage/userData.json', JSON.stringify(userData, null, 2), (err) =>{
    if (err) console.error(err);
  });
}

module.exports.config = {
  command: "~~"
}
