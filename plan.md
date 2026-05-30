
# General Idea
A life simulation based off of Catan in which multiple civilizations are built and simulated based on a series of variables. These variables include access to resources, alliances and wars, and aspects of society like education, training, and housing

## Resources
There are 5 core resources in Yonder: Water, Ore, Livestock, Crop, Water
These resources are used to build things within a civilization

Another key resource is the population of the civ.

## Decision Making Framework
Every civilization will have a leader with a set of sliders (the leader is just an ideology for now, but can later have elections or other things like that). These sliders dictate that civilization's decisions based on their views on certain aspects of leading the civilization. The slider options are used for weighting decisions, and are: Aggression, Diplomacy, Fiscal, Tradition, Flexibility

Aggression: High Agression means the civ will start more fights and retaliate more often. They still need reasons do this, but often it may just be that there are easy targets. They will also attempt to make larger bets on risky moves.
Diplomacy: High Diplomacy means the civ will focus on building relationships with other nations and trying to keep fights to a minimum. They will also attempt to trade much more often.
Fiscal: High Fiscal means the civ will focus on saving resources or investing in the future instead of spending in the present. Low fiscal will have a civilization spend most resources as soon as they get them and use them to stimulate the population currently.
Tradition: High Tradition means the civ will focus on expanding under the same formula instead of focusing on making new things. They will have higher birth rates but lower education
Flexibility: High Flexibility means that the above decision making weights will vary by quite a bit. They will often analyze the high and low ends of the decision and pick the one with the highest expected outcome.

Each time a decision can be made, that decision will have a weight in each of these aspects, the decision with the smallest difference in weights from the civ's weights will have the highest score, and be chosen.

## Civs Mechanics

A civ has a few stats that dictate how it performs during actions.

- Smarts: How educated the civ is, categorized in ages (ie Stone, Middle, Magic/Modern). Allows for more technology and options to spend resources on.
- Happiness: How happy the civ is, from 1-100, and dictates birth rates and productivity
- Strength: How powerful the civ is, dictates success in battle and productivity

A civ follows the cycle:
- Acquire resources
- Spend resources to upgrade
- Aquire resources at a faster rate

A civ can spend resources on housing, production for either of the 5 resources, ammenities, training, or education.

## The Fields

The fields is the world Yonder is set in. It is procedurally generated through a seed, and shows where the resources of the world are located. When attempting to produce a resource, the civilization must be located close to the tile with the resource. This distance is calculated from the distance to the civ center, but is reduced as the city expands (higher population).

Only one civ can harvest a certain resource tile, which can cause conflicts.

## Actions

Civs can take actions or be prompted with them, often as the result of other civ's actions, but sometimes due to natural events called World Actions.

Civ Actions:
- Trade: Trade with another civ
- Battle: Attack another civ
- Build: Build an aspect of the civ.
- Speak: Propose deals with another civ and make alliances
- Invest: Send resources to other civs for more in return later

World Actions:
- Natural Disasters: Tornados, Droughts, Fire
- New Civ: Splinter civ appears
- Barbarians: Invading forces come to attack from Elsewhere
- Discovery: A well of resources is discovered or a new technology is learned by all


A civ can take as many actions as it wishes, but often its weights will prefer to take no actions at that point.


## Additional Goals

- Let the user input starting parameters
- Let the user act for a civilization
- Let the user trigger World Actions


