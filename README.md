# Twtich-Plays-Video-Games
A chat bot written in C++ for twitch plays channels. 
This is a reconfigurable chat bot that can play most games just fine - for now keyboard keys are hard coded but will soon be remappable.

**Services:**
This chat Bot works with Twitch but a Youtube Gaming feature is planned to be added in the near future.

**TODO:**
rewrite the connection class to make cleaner code and enable the youtube gaming feature.
add a plugin system for programmers to add features specific to a game they're streaming.

**Usage:**
First and formost this Bot is in beta as such extra setup steps will be required until later development.

1. you **MUST** have and oauth token for this bot to work it can be obtained here: https://twitchapps.com/tmi/ 

run the program once setting’s.json appears open it with a compatible text editor i'd reccomend notepad++ 
add the name of your channel without a pound sign the oauth token into the 
setting's file and save it. Note  the service option isn't finished yet so don't bother commands.txt can be 
loaded by obs to show the command queue on stream. 

**FAQ:**

**Q:** How many commands can this bot take?

**A:** Pending further testing

**Q:** I want a queue log to appear onscreen?

**A:** this program automatically generates a commands.txt file that can be used in conjunction with OBS to show what's currently on queue. 


**Built with:**
 Nlohmann json library: https://github.com/nlohmann/json
