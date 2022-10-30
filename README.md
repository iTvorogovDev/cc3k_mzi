# cc3k_mzi
C++ command line-based dungeon crawler

# DISCLAIMER
The code provided in this repository is meant **ONLY** as a portfolio entry for the potential employer's consideration. Reusing any code provided here in your own assignments is an academic offense.

# TECHNICAL SPECIFICATIONS
1. Built and tested in Bash environments on Linux and MinGW; should work with both
2. C++ code compiled with g++

# INSTRUCTIONS
1. From within the root folder, run make command
2. Run the "master" executable in terminal

# HOW TO PLAY

## Basics
1. Start the game by choosing your character's race. The player character (PC) is denoted by the '@' symbol on the board. The following options are available, each with its own starting stats and traits:
  - Shade - 125 HP, 25 Atk, 25 Def
  - Drow - 150 HP, 25 Atk, 15 Def, all potions' effects magnified by 1.5
  - Vampire - 50 HP, 25 Atk, 25 Def, gains 5 HP on every successful attack, no maximum HP
  - Troll - 120 HP, 25 Atk, 15 Def, regains 5 HP, HP is capped at 120
  - Goblin - 110 HP, 15 Atk, 20 Def, steals 5 gold from every slain enemy
2. The game ends when you reach the stairs on floor 5 or the PC's health reaches 0
3. Enemies are shown on the board by the bracketed letter of their type. The following enemies inhabit the dungeon:
  - (H)uman - 140 HP, 20 Atk, 20 Def, drops 2 normal piles of gold
  - D(W)arf - 100 HP, 20 Atk, 30 Def, Vampires are allergic to dwarves and lose 5HP rather than gain
  - (E)lf - 140 HP, 30 Atk, 10 Def, gets two attacks against every race except drow
  - (O)rc - 180 HP, 30 Atk, 25 Def, does 50% more damage to goblins
  - (M)erchant - 30 HP, 70 Atk, 5 Def, neutral by default, attacking a Merchant makes every Merchant hostile
  - (H)alfling - 100 HP, 15 Atk, 20 Def, has a 50% chance to evade the PC's attack
  - (D)ragon - 150 HP, 20 Atk, 20 Def, always guards a treasure hoard.

 ## Scoring
Score is determined by the amount of gold the player collects before reaching the end or falling in combat. Gold is shown on the board with the 'G' letter. All enemies drop a pile of gold upon being defeated, which is automatically added to the player's score. To pick up a pile of gold on the floor, simply walk over it. A dragon's hoard can only be picked up if the dragon guarding it is slain.

## Potions
Potions are the only other loot besides gold in the game. The effects of a particular potion are not known until it is used for the first time. The following potion types can be found in the dungeon:

1. Positive potions
- Restore health (RH): restore up to 10 HP (cannot exceed maximum prescribed by race)
- Boost Atk (BA): increase Atk by 5
- Boost Def (BD): increase Def by 5

2. Negative potions
- Poison health (PH): lose up to 10 HP (cannot fall below 0 HP)
- Wound Atk (WA): decrease Atk by 5
- Wound Def (WD): decrease Def by 5

## Combat
1. Enemies will auto-attack the PC, however, there is a 50% chance their attack misses. The PC has the option of attacking any of the 8 squares adjacent to them and within a 1-block radius. The PC never misses (unless fighting a Halfling). 
2. Damage is calculated as follows: Damage(Defender) = ceiling((100=(100+Def(Defender)))Atk(Attacker)), where Attacker specifies the attacking character (enemy or PC) and defender specifies the character being attacked. Thus, in a single round a character can be both an attacker and a defender.

## Controls
To play the game, enter a command into the terminal. The following commands are accepted:
1. **no,so,ea,we,ne,nw,se,sw** - moves the player character one block in the specified cardinal direction.
2. **u \<direction>** - uses the potion indicated by the direction
3. **a \<direction>** - attacks the enemy in the specified direction, if the enemy is in the immediately specified block
4. **s, d, v, g, t** - specifies the race the player wishes to be when starting a game.
5. **f** - stops the enemies from moving, until the command is supplied again. CHEATING.
