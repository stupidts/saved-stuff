var fs = require('fs');
var txtName = JSON.parse(fs.readFileSync('Storage/txtName.json', 'utf8'));
var logs = fs.readFileSync(`logs/${txtName.text}.txt`, 'utf8');

function hook(channel, title, message, color, avatar) {

  if (!channel) return console.log("Channel not found.");
  if (!title) return console.log("Title not found.");
  if (!message) return console.log("Message not found.");
  if (!color) color = "696969";
  if (!avatar) avatar = "https://cdn.discordapp.com/attachments/420745531896365066/441322763693850624/WHO90x90.png"

  color = color.replace(/\s/g, '');
  avatar = avatar.replace(/\s/g, '');

  channel.fetchWebhooks()
    .then(webhook => {
      let foundHook = webhook.find('name', 'Webhook');

      if (!foundHook) {
        channel.createWebhook('Webhook', 'https://cdn.discordapp.com/attachments/420745531896365066/441322763693850624/WHO90x90.png')
          .then(webhook => {
            webhook.send(' ', {
              "username": title,
              "avatarURL": avatar,
              "embeds": [{
                "color": parseInt(`0x${color}`),
                "description": message
              }]
            })
            .catch(error => {
              console.log(error);
              return channel.send('**Something went wrong when sending the webhook. Please check console');
            })
          })
      } else {
        foundHook.send(' ', {
          "username": title,
          "avatarURL": avatar,
          "embeds": [{
            "color": parseInt(`0x${color}`),
            "description": message
          }]
        })
        .catch(error => {
          console.log(error);
          return channel.send('**Something went wrong when sending the webhook. Please check console');
        })
      }
      })
}
exports.hooks = async (channel, title, message, color, avatar) => {
  hook(channel, title, message, color, avatar);
}
