# zHackChest
### *Forcing open chests and doors using dexterity/strength/mana*

This plugin exists to easy up a little bit opening chests and doors.  
Of course it only works with MOBs that can be opened with a lockpick, and requires to learn the lockpicking talent beforehand.

[![Presentation](https://img.youtube.com/vi/q2WW9UpY1yo/maxresdefault.jpg)](https://youtu.be/q2WW9UpY1yo)
<p align="center">
Video recorded in Masty's L'Hiver Edition v1.6.4, but also tested in G1, G2NotR, and in The Chronicles of Myrtana.</br>
Should work with any mod, but if there is any problem, let me know.
</p>

Default settings:
|Setting|Default value|Description|
|-------|-------------|-----------|
|HotKeyStr|KEY_T|HotKey for using strength points to open|
|HotKeyDex|KEY_Y|HotKey for using dexterity points to open|
|HotKeyMan|KEY_U|HotKey for using mana points to open|
|BaseLevel|20||
|AttPerLevel|5||

Everything configurable in Gothic.ini

Formula for calculating the needed attribute points:
```
BaseLevel + (X * AttPerLevel)
```
X is length of the picklock string, BaseLevel and AttPerLevel depends on the settings  
e.g. Picklock string is "LRRLLRL" (length is 7) and using default settings then attribute points needed to open something is 20 + (7 * 5) = 55

For both Strength and Dexterity there is small percentage chance that opening will fail, if player attribute is below 100.

### Dexterity
Of course you need at least one lockpick in your equipment and every try uses up one, both on fail and success.

### Mana
100% chance to open, but if player max mana is below 100, or max mana is equal to mana needed, it will launch a bit longer animation.  
Short animation - FX from spell Charm and animation like shooting a projectile spell  
Long animation - FX and animation from Teleport spell  

### Strength
Basically you need a weapon to open something using strength attribute, with an exception on doors, where you can use kick without a weapon.  
If you are opening doors with a kick and fail, player will fall down on the floor.  
If you are opening anything with a weapon and fail, it will just not open and you need to try again.  
(Maybe I'll add losing some health points on fail, to imitate the weapon bouncing back or something?)

## Requirements
[Union](https://worldofplayers.ru/threads/40376/)  
[zParserExtender](https://worldofplayers.ru/threads/41999/) - Only for Union versions below 1.0m, as from this version plugin is fully integrated

## Installation
Put **zHackChest.vdf** inside */Data/Plugins*

#### Mirrors
[MEGA.nz](https://mega.nz/folder/WoQTjZqK#5e-_C8BCS_8tUO2U3g8PiA)
