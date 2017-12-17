# Twtich-Plays-Video-Games
A chat bot written in C++ for twitch plays channels. 
This is a reconfigurable chat bot that can play most games just fine - for now keyboard keys are hard coded but will soon be remappable.

**Services:**
This chat Bot works with Twitch but a Youtube Gaming feature is planned to be added in the near future.

**What work's / what doesn't:**
Game's wise I'm not entirely sure what games don't work.
The setting’s button doesn’t make good files
Feature's wise Youtube gaming isn't added.

**TODO:**
rewrite the connection class to make cleaner code and enable the youtube gaming feature.
change keyboard class to work with broken games.
add a plugin system for programmers to add features specific to a game they're streaming.

**Usage:**
run the program once setting’s. json appears open it with a compatible text editor add the name of your channel 
without a pound sign the oauth token and the bot's name into the setting's file and save it. 
not service isn't finished yet so don't bother. commands.txt can be loaded by obs to show the command queue on stream. 

**FAQ:**

**Q:** Why won’t my game play??
**A:** When working with software input in operating systems there's several different types of keyboard input ranging from 
virtual key presses sent through the windows messaging layer to scan codes and several other layes of input, games read from different 
areas of input in their own way that might not allow this Chat Bot to register 

**Q:** How many commands can this bot take?

**A:** Pending further testing

**Q:** I want a queue log to appear onscreen?

**A:** this program automatically generates a commands.txt file that can be used in conjunction with OBS to show what's currently on queue. 

Using Nlohmann json library: https://github.com/nlohmann/json
