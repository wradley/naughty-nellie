# Naughty Nellie... for lack of a better name

### Notes
1. Entities are defined AND instantiated
  * Entities are defined with a simple virtual machine in little script files
  * Entities are instantiated from a save file with their definition numbers and can easily be modified (for frequent game saves and loads)
  * There are two different forms of ids.
    * An instance id (every time an ent is brought into this world--run time)
    * A define id (when an entity is defined--before run time)
2. Nellie uses the Entity-Component-System model
  * An entity is just an id number. Not a define id (used for creating entities) but an instance id (defined upon creating the entity)
    * For example a define id could be 12 for a tree there could be hundreds of trees so each tree has its own instance id
  * A component defines something really simple and can be refered to (in a system) by its entity id
    * Graphics component, audio component, collision component, ect...
  * The system is just a big container that does all the changes to the components
