console.log("Starting Bot...");

const Discord = require('discord.js');
const bot = new Discord.Client();
const prefix = '!';
var fs = require('fs');
const ytdl = require('ytdl-core');
const hooks = require('./hooks.js');
const shop = require('./shop.js');
const who = require('./who.js');

var song = '';
const active = new Map();

let enemyList = [];

let loopEnabled = false;

var FullMessage = '';
var date = new Date();
var txtName = JSON.parse(fs.readFileSync('Storage/txtName.json', 'utf8'));
var reminders = JSON.parse(fs.readFileSync('Storage/reminders.json', 'utf8'));
let txt = txtName;
var logs = fs.readFileSync(`logs/${txtName.text}.txt`, 'utf8');

var userData = JSON.parse(fs.readFileSync('Storage/userData.json', 'utf8'));
var config = JSON.parse(fs.readFileSync('Storage/config.json', 'utf8'));
var enemies = JSON.parse(fs.readFileSync('Storage/enemies.json', 'utf8'));



bot.commands = new Discord.Collection();
fs.readdir('./commands/', (err, files) => {
  if (err) console.error(err);
  var jsfiles = files.filter(f => f.split('.').pop() == 'js');
  if (jsfiles.length <= 0) {return console.log('No commands found...')}
  else { console.log(jsfiles.length + ' commands found.')}

  jsfiles.forEach((f, i) => {
    var cmds = require('./commands/' + f);
    console.log('Command ' + f + ' loading...');
    bot.commands.set(cmds.config.command, cmds);
  });
});


//Log Stuffs
function newtxt()
{
  // console.log("Creating new text file");
  fs.appendFile(`logs/${txtName.text}.txt`, 'New Log!', function (err) {
  if (err) throw err;
  });
}
function wait(ms){
   var start = new Date().getTime();
   var end = start;
   while(end < start + ms) {
     end = new Date().getTime();
  }
}
function textinfo()
{
  // console.log(`Setting txt to txtName - txtName = ${txtName.text}`);
  txt = txtName.text;
  // console.log("Adding 1 to txt");
  txt += 1;
  // console.log("txtName = txt");
  if (txtName.text !== txt) txtName = {text: txt}
  // console.log(`Writing txtName.json - txtName = ${txtName.text}`);
  fs.writeFile('Storage/txtName.json', txtName, (err) =>{
    if (err) console.error(err);
  });
  // console.log("Waiting 1 second");
  // wait(1000);
  // console.log("newtxt();");
  newtxt();
  console.log(`New log: ${txtName.text}`);
}
function Loop()
{
  if (loopEnabled)
  {
    console.log("Starting logs");
    restartLoop:
    while (true) {
      for (var i=0; i <= 5e+5; i++) {
          console.log(i);
        if (i >= 5e+5)
          {
            textinfo();
            // console.log("restartLoop");
            continue restartLoop;
          }
      }
      break;
    }
    /*restartLoop:
    while(true){
      do {
        cLog++;
        // console.log(cLog);
      }
      while (cLog < 1000000)
      cLog = 0;
      txt += 1;
      txtName = {text: txt}
      fs.writeFile('Storage/txtName.json', JSON.stringify(txt), (err) =>{
        if (err) console.error(err);
      });
      wait(1000);
      newtxt();
      console.log(`New log: ${txtName}`);
    }*/
  }
}
//End Log Stuffs

bot.on('messageUpdate', (oldMessage, newMessage) => {
  var sender = oldMessage.author;
  var fullMessageOLD = oldMessage.content;
  var fullMessageNEW = newMessage.content;
  FullMessage = (`[UpdateOld][${oldMessage.channel.name}] ${sender.id} ${sender.username}: ${fullMessageOLD}\r\n[UpdateNew][${newMessage.channel.name}] ${sender.id} ${sender.username}: ${fullMessageNEW}\r\n`);
  console.log(FullMessage);
  fs.appendFileSync(`logs/${txtName.text}.txt`, FullMessage, (err) =>{
    if (err) console.error(err);
  });
});
bot.on('userUpdate', (oldUser, newUser) => {
  FullMessage = (`[UserOld] ${oldUser.id} ${oldUser.username}#${oldUser.discriminator} ${oldUser.avatarURL}\r\n[UserNew] ${newUser.id} ${newUser.username}#${newUser.discriminator} ${newUser.avatarURL}\r\n`);
  console.log(FullMessage);
  fs.appendFileSync(`logs/${txtName.text}.txt`, FullMessage, (err) =>{
    if (err) console.error(err);
  });
});
bot.on('guildMemberUpdate', (oldUser, newUser) => {
  if (oldUser.nickname == null) oldUser.nickname = oldUser.user.username;
  if (newUser.nickname == null) newUser.nickname = newUser.user.username;
  FullMessage = (`[GMUpdateOld] ${oldUser.user.id} ${oldUser.user.username} ${oldUser.roles} ${oldUser.nickname}\r\n[GMUpdateNew] ${newUser.user.id} ${newUser.user.username} ${newUser.roles} ${newUser.nickname}\r\n`);
  console.log(FullMessage);
  fs.appendFileSync(`logs/${txtName.text}.txt`, FullMessage, (err) =>{
    if (err) console.error(err);
  });
});
bot.on('messageDelete', message => {
  var sender = message.author;
  var fullMessage = message.content;
  FullMessage = (`[Delete][${message.channel.name}] ${sender.id} ${sender.username}: ${fullMessage}\r\n`);
  console.log(FullMessage);
  fs.appendFileSync(`logs/${txtName.text}.txt`, FullMessage, (err) =>{
    if (err) console.error(err);
  });
});
/*bot.on('typingStart', (channel, user) => {
  var sender = user;
  FullMessage = (`[TStart][${channel.name}] ${sender.id} ${sender.username}\r\n`);
  console.log(FullMessage);
  fs.appendFileSync(`logs/${txtName.text}.txt`, FullMessage, (err) =>{
    if (err) console.error(err);
  });
});
bot.on('typingStop', (channel, user) => {
  var sender = user;
  FullMessage = (`[TStop][${channel.name}] ${sender.id} ${sender.username}\r\n`);
  console.log(FullMessage);
  fs.appendFileSync(`logs/${txtName.text}.txt`, FullMessage, (err) =>{
    if (err) console.error(err);
  });
});*/
/*bot.on('messageReactionAdd', (message, user) => {
  var sender = message.author;
  var fullMessage = message.content;
  FullMessage = (`[ReactAdd][${message.channel.name}] ${sender.id} ${sender.username}: ${fullMessage}\r\n`);
  console.log(FullMessage);
  fs.appendFileSync(`logs/${txtName.text}.txt`, FullMessage, (err) =>{
    if (err) console.error(err);
  });
});
bot.on('messageReactionRemove', (message, user) => {
  var sender = message.author;
  var fullMessage = message.content;
  FullMessage = (`[ReactDel][${message.channel.name}] ${sender.id} ${sender.username}: ${fullMessage}\r\n`);
  console.log(FullMessage);
  fs.appendFileSync(`logs/${txtName.text}.txt`, FullMessage, (err) =>{
    if (err) console.error(err);
  });
});*/
/*bot.on('guildMemberSpeaking', (member, speaking) => {
  var sender = member.user;
  if(speaking) FullMessage = (`[StartSpeak] ${sender.id} ${sender.username}\r\n`);
  else FullMessage = (`[StopSpeak] ${sender.id} ${sender.username}\r\n`);
  console.log(FullMessage);
  fs.appendFileSync(`logs/${txtName.text}.txt`, FullMessage, (err) =>{
    if (err) console.error(err);
  });
});*/





bot.on('message', message => {
  //Basic info
  var sender = message.author;
  var msg = message.content.toLowerCase();
  var cont = message.content.slice(prefix.length).split(" ");
  var args = cont.slice(1);
  var cont2 = message.content.split(" ");
  var content = cont2[0];
  var fullMessage = message.content;
  // console.log(fullMessage, sender.id);
  // console.log(content); console.log(args);

  //log Stuffs
  FullMessage = (`[Message][${message.channel.name}] ${sender.id} ${sender.username}: ${fullMessage}\r\n`);
  console.log(FullMessage);
  fs.appendFileSync(`logs/${txtName.text}.txt`, FullMessage, (err) =>{
    if (err) console.error(err);
  });

  //Auto Set Stats
  if (!userData[sender.id])
  {
    userData[sender.id] = {
    userName: sender.username,
    messagesSent: 0,
    gay: 0,
    whosCollected: 0,
    weapon: 'Unarmed',
    armor: 'No Armor',
    weaponValue: 0,
    armorValue: 0
    }
    fs.writeFile('Storage/userData.json', JSON.stringify(userData, null, 2), (err) => {
      if (err) console.error(err);
    });
  }
  userData[sender.id].messagesSent++;
  fs.writeFile('Storage/userData.json', JSON.stringify(userData, null, 2), (err) => {
    if (err) console.error(err);
  });

  // console.log(sender.id);
  // console.log(sender);

  //OI stuff (not working)
  let newoi = '';
  if(config.oi == true) {
    let oi = message.content.split("");
    oi.forEach(function(char){
      if(char == "A" || char == "E" || char == "I" || char == "O" || char == "U")
      {
        console.log(char + ' is replaced with Oi');
        charOi = "Oi";
        newoi = newoi.concat(charOi);
      }
      else if(char == "a" || char == "e" || char == "i" || char == "o" || char == "u")
      {
        console.log(char + ' is replaced with oi');
        charoi = "oi";
        newoi = newoi.concat(charoi);
      }
      else
      {
        console.log(char + ' is replaced with ' + char);
        newoi = newoi.concat(char);
      }
    })
    console.log(newoi);
  }

  if (message.content.toLowerCase().includes('spam me'))
  {
    for (var i = 0; i < 51; i++) {
      message.author.send('__***SPAM INBOUND***__');
    }
  }

  //debug
  if (message == prefix + '~~g_r~~;' && sender.id == 265957683260030976){
    console.log(message.guild.roles);
    message.delete();
  }
  if (message == prefix + '~~c_log~~;' && sender.id == 265957683260030976){
    console.log(message.author.username + ', ' + message.channel.id + ', ' + config.channelID);
    message.delete();
    textinfo();
  }

    //view messages and gay
    if(message.content == prefix + 'messages')
    {
      message.channel.send({embed:{
        author: {
          name: sender.username,
          icon_url: sender.avatarURL
        },
        fields: [
          {
            name: 'Sent Messages',
            value: 'You sent ' + userData[sender.id].messagesSent + ' messages!'
          }
        ]
      }})
    }
    if(message.content == prefix + 'howgay')
    {
      message.channel.send({embed:{
        author: {
          name: sender.username,
          icon_url: sender.avatarURL
        },
        fields: [
          {
            name: 'How gay are you?',
            value: 'You have ' + userData[sender.id].gay + ' gay!'
          }
        ]
      }})
    }
    //End view messages and gay

  //good morning
  if (message.author.id != 413902897101930497)
  {
    let nick = sender.nickname;
    if (nick == undefined || nick == NULL || nick == '')
    {
      nick = sender.username;
    }
    if (message.content.toLowerCase().includes('good morning'))
    {
      console.log(sender + ' says good morning');
      message.channel.send('Good morning ' + nick + '!');
    }//good afternoon
    if (message.content.toLowerCase().includes('good afternoon'))
    {
      console.log(sender + ' says good afternoon');
      message.channel.send('Good afternoon ' + nick + '!');
    }//good evening
    if (message.content.toLowerCase().includes('good evening'))
    {
      console.log(sender + ' says good evening');
      message.channel.send('Good evening ' + nick + '!');
    }//good night
    if (message.content.toLowerCase().includes('good night'))
    {
      console.log(sender + ' says good night');
      message.channel.send('Good night ' + nick + '!');
    }
    if (message.content.toLowerCase() == 'mornin')
    {
      console.log(sender + ' says mornin');
      message.channel.send('Mornin ' + nick + '!');
    }
    if (message.content.toLowerCase() == 'lenny')
    {
      message.delete();
      message.channel.send('( ͡° ͜ʖ ͡°)');
    }
    if (message.content.toLowerCase().includes('14 9 7 7 5 18') || message.content.toLowerCase().includes('14-9-7-7-5-18') || message.content.toLowerCase().includes('1⃣ 4⃣ 9⃣ 7⃣ 7⃣ 5⃣ 1⃣ 8⃣'))
    {
      message.channel.send('Overused much 👎');
      message.author.send('Overused much 👎');
      message.member.setNickname('I\'m hella gay');
    }
    if (message.content.toLowerCase().includes('benis'))
    {
      message.member.setNickname('benis');
      message.channel.send('You are now a benis!');
    }
    if (message.content.toLowerCase() == 'ping')
    {
      message.channel.send('pong');
    }
    if (message.content.toLowerCase() == 'bing')
    {
      message.channel.send('bong');
    }




    //reminder system
    if (message.content.toLowerCase().startsWith('!remind'))
    {
      var remindCount = 21;
      if (reminders[0] == null) // makes sure that the default reminder gets added if the file gets wiped
      {
        if (!reminders[0]) reminders[0] = {text : '!remind whatever reminder you want after the command will save.'};
      }
      if (args[0] == null) // if nothing is typed after !remind (shows all reminders)
      {
        var temp = "";
        for (var i = 0; i < remindCount; i++) {
          if (!reminders[i])reminders[i] = {text: " ", user: sender.id}
          if (reminders[i].text == " ")
            break;
          temp += `${i}. ${reminders[i].text.toString()}\n`;
        }
        console.log(temp);
        message.channel.send({embed:{
          author: {
            name: sender.username,
            icon_url: sender.avatarURL
          },
          fields: [
            {
              name: 'Reminders!',
              value: temp
            }
          ]
        }})
      }
      else if (args[0].toLowerCase() == 'clear') // clears all reminders from the list
      {
        if (sender.id == 265957683260030976)
        {
          for (var i = 1; i < remindCount; i++) {
            reminders[i].text = " ";
            reminders[i].user = null;
          }
          message.channel.send("Cleared all reminders!");

          fs.writeFile('Storage/reminders.json', JSON.stringify(reminders, null, 2), (err) => {
            if (err) console.error(err);
          });
        }
        else
        {
          message.channel.send("You do not have permission to clear all reminders!");
        }
      }
      else if (args[0].toLowerCase() == 'edit') // edit a requested reminder
      {
        var num = args[1];
        if (num != null)
        {
          if (reminders[num].text != " ")
          {
            if (reminders[num].user == sender.id || reminders[num].user == null)
            {
              if (num < 10) reminders[num].text = message.content.slice(14, message.content.length);
              else reminders[num].text = message.content.slice(15, message.content.length);
              message.channel.send(`Edited reminder ${num}!`);

              fs.writeFile('Storage/reminders.json', JSON.stringify(reminders, null, 2), (err) => {
                if (err) console.error(err);
              });
            }
            else {
              message.channel.send("That reminder is set by a different user! (Ask WHO? for help.)");
            }
          }
          else {
            message.channel.send("That reminder does not exist!");
          }
        }
        else {
          message.channel.send("Please specify a list number to *edit*. (Must be a reminder you created!)");
        }
      }
      else if (args[0].toLowerCase() == 'remove') // removes a requested reminder
      {
        var num = args[1];
        if (num != null)
        {
          if (reminders[num].text != " ")
          {
            if (reminders[num].user == sender.id || reminders[num].user == null)
            {
              reminders[num].text = " ";
              reminders[num].user = null;
              message.channel.send(`Removed reminder ${num} from the list!`);

              for (var i = 1; i < remindCount; i++) {
                if (reminders[i].text == " ")
                {
                  // console.log(`I reminder ${i}i was empty!`);
                  for (var j = i; j < remindCount; j++) {
                    if (reminders[j].text != " ")
                    {
                      // console.log(`J reminder ${j}j was empty!`);
                      reminders[i].text = reminders[j].text;
                      reminders[j].text = " ";
                      // if (reminders[i].text != " ")
                      //   console.log(`J reminder ${i}i is no longer empty!`);
                      break;
                    }
                  }
                }
              }
              fs.writeFile('Storage/reminders.json', JSON.stringify(reminders, null, 2), (err) => {
                if (err) console.error(err);
              });
            }
            else {
              message.channel.send("That reminder is set by a different user! (Ask WHO? for help.)");
            }
          }
          else {
            message.channel.send("That reminder does not exist!");
          }
        }
        else {
          message.channel.send("Please specify a list number to *remove*. (Must be a reminder you created!)");
        }
      }
      else if (args[0].toLowerCase() == 'shift') // shifts a requested reminder
      {
        var num = args[1];
        var pos = 1;
        var temp4 = " ";
        if (num != null)
        {
          if (reminders[num].text != " ")
          {
              temp4 = reminders[num].text;
              pos = args[2];
              message.channel.send(`Shifted reminder ${num} to position ${pos}! (Not really this is WIP)`);



              fs.writeFile('Storage/reminders.json', JSON.stringify(reminders, null, 2), (err) => {
                if (err) console.error(err);
              });
            }
          else {
            message.channel.send("That reminder does not exist!");
          }
        }
        else {
          message.channel.send("Please specify a list number to *shift*. (moves the reminder and shifts the rest down)");
        }
      }
      else if (args[0].toLowerCase() == 'help')
      {
        message.channel.send({embed:{
          author: {
            name: sender.username,
            icon_url: sender.avatarURL
          },
          fields: [
            {
              name: 'Reminders!',
              value: "Commands for reminders are:\n!remind (views the list of reminders)\n!remind <if you type here without the arrows it will save the entire message>"+
                                   "\n!remind edit <number> (edits a reminder you have set)\n!remind remove <number> (removes a reminder you have set)"
            }
          ]
        }})
      }
      else { // if nothing is true then save a reminder
        var temp2 = true; // here so that the loop doesn't set every reminder to one thing
        var temp3 = 1;
        for (var i = 1; i < remindCount; i++) {
          temp3 = i;
          if (reminders[i].text == " " && temp2)
          {
            console.log(`reminders[${i}] == null`);
            if (!reminders[i].user || !reminders[i].text) reminders[i] = {text: " ", user: null}
            reminders[i].text = message.content.slice(8, message.content.length);
            reminders[i].user = sender.id

            message.channel.send(`Saved your reminder in position ${i}`);

            i = -1;
            temp2 = false;
            fs.writeFile('Storage/reminders.json', JSON.stringify(reminders, null, 2), (err) => {
              if (err) console.error(err);
            });
          }
        }
        if (temp3 >= 20 && reminders[20].text != " ")
        {
          message.channel.send("There are too many reminders in the list right now (MAX 20)");
        }
      }
    }
  }


  //gay
  if (message.content.toLowerCase().includes('gay') && message.author.id != 413902897101930497)
  {
    userData[sender.id].gay++;
    fs.writeFile('Storage/userData.json', JSON.stringify(userData, null, 2), (err) => {
      if (err) console.error(err);
    });
  }




  //----------------commands and stuff-------------------
  if(message.channel.id == config.channelID || message.author.id == 265957683260030976 || message.channel.type == 'dm')
  {
    if (sender.id == '413902897101930497')
    {return;}


    //replys to bot dms
    if (message.channel.type == 'dm')
    {
      let user = bot.fetchUser(265957683260030976)
      .then(user => {
        user.send({embed:{
          author: {
            name: sender.username,
            icon_url: sender.avatarURL
          },
          fields: [
            {
              name: 'You recieved a message!',
              value: message.content
            }
          ]
        }});
        console.log(user.username + ' ' + user.id + ' has recieved a secret message from ' + message.author.username, + ' ' + message.author.id);
      });
    }
    //

    // if (!message.content.startsWith(prefix)) return; //commands require a prefix
    // console.log(sender.username + " " + fullMessage);

    //PURGE
    if (message.content.startsWith(prefix + 'purge') && sender.id == 265957683260030976)
    {
      async function purge()
      {
        message.delete();

        if(isNaN(args[0]))
        {
          console.log("Error purging! Need value!");
        }

        const fetched = await message.channel.fetchMessages({limit: args[0]});
        console.log(fetched.size + " messages will be purged!");

        message.channel.bulkDelete(fetched)
        .catch(error => message.channel.send(`Error: ${error}`));
      }
      purge();
    }
    //End PURGE
    //BURGE
    if (message.content.startsWith(prefix + 'burge') && sender.id == 265957683260030976)
    {
      async function burge()
      {
        message.delete();

        if(isNaN(args[0]))
        {
          console.log("Error purging! Need value!");
        }

        const fetched = await message.channel.fetchMessages({limit: args[0]});
        console.log(fetched.size + " messages will be Burged!");

        for (var i = 0; i < args[0]; i++) {
          bot.TextChannel.fetchMessage(fetched[i].id)
            .then(message => message.edit(":b:URGE!"));

        }
      }
      burge();
    }
    //End BURGE

    if (msg.startsWith(prefix + 'hook'))
    {
      message.delete();

      if (message.content == prefix + 'hook') {return hook(message.channel, 'Hook Usage', `${prefix}hook <title>, <message>, [HEXcolor], [avatarURL]`,'696969',`https://cdn.discordapp.com/attachments/420745531896365066/441322763693850624/WHO90x90.png`);}

      let hookArgs = message.content.slice(prefix.length + 4).split(",");

      hooks.hooks (message.channel, hookArgs[0], hookArgs[1], hookArgs[2], hookArgs[3]);
    }
    //Bot shutdown
    if (message.content == prefix + 'shutdown' && message.author.id == 265957683260030976)
    {
      message.channel.send('WHO? Bot is now offline.');
      console.log('~~BOT SHUTDOWN~~');
      bot.destroy();
    }


    //Lottery Commands
    if (content == prefix + 'lottome')
    {
      let lottoRole = message.guild.roles.find(role => role.name === "Lottery");
      message.member.addRole(lottoRole);
      message.channel.send({embed:{
        author: {
          name: sender.username,
          icon_url: sender.avatarURL
        },
        fields: [
          {
            name: 'WHO? Lottery!',
            value: 'Gave ' + message.author.nickname + ' access to the WHO? Lottery!'
          }
        ]
      }})
    }

    if (content == prefix + 'who' && message.channel.id == config.channelID2)
    {
        who.who(bot, message, args, userData);
    }
    //End Lottery Commands

    //Shop commands
    if (content == prefix + 'shops') {console.log('Shops();'); /*shop.list(bot, message, args);*/}
    //End Shop commands

    //Other Commands
    if (content == prefix + 'stats') {console.log('Stats();'); hooks.hooks(message.channel, 'Stats', ('Username: ' + sender.username + ' \nWHO?\'s collected: ' + userData[sender.id].whosCollected + ' \nWeapon: ' + userData[sender.id].weapon + ' \nArmor: ' + userData[sender.id].armor), '696969', 'https://cdn.discordapp.com/attachments/420745531896365066/475542984465580032/WHOStats.png');}
    //End Other Commands

    var cmd = bot.commands.get(cont[0]);
    if (cmd) cmd.run(bot, message, args, userData);
  }
});

//When a member joins
bot.on('guildMemberAdd', member => {
  console.log('User: ' + member.user.username + ' has joined the server.');
  member.addRole(member.guild.roles.find(role => role.name === "Normies"));
});
// When a member leaves
bot.on('guildMemberRemove', member => {
  console.log('User: ' + member.user.username + ' has left the server.');
});


bot.on('ready', () => {
  /*enemies = {
    level1: ['Scarecrow', 'Rock', 'Tree', 'Goose', 'Fish'],
    level2: ['Raven', 'Bull', 'Boar', 'Eagle', 'Porcupine'],
    level3: ['Troll', 'Grunt', 'Mage', 'Slinger', 'Shank'],
    level4: ['Bear', 'Lion', 'Crocodile', 'Snapping Turtle'],
    level5: ['Flamethrower Gnome', 'Shield Gnome', 'Slasher Gnome', 'Trap Gnome'],
    level6: ['Berserker Viking', 'Throwing Axe Viking', 'Battle Axe Viking'],
    level7: ['Dude with a Katana', 'Dude with Nunchucks', 'Dude with Boxing Gloves', 'Dude with Brass Knuckles'],
    level8: ['Wraith', 'Reaper', 'Banshee'],
    level9: ['Paladin', 'Knight', 'Warrior'],
    level10: ['WHO?\'s Guard', 'WHO?\'s Knave'],
    levelUnknown: ['Lego Brick', 'Ant', 'Table', 'Mystery Man', 'SANIC']
  }
  fs.writeFile('Storage/enemies.json', JSON.stringify(enemies), (err) =>{
    if (err) console.error(err);
  });*/
  console.log("Bot Online!")
  bot.user.setStatus('Online');
  bot.user.setActivity('!help | WHO? Bot');
})































bot.login('NDEzOTAyODk3MTAxOTMwNDk3.DYC_OQ.I_qYkSYpGjazywliyOPCHTRmmQE');
