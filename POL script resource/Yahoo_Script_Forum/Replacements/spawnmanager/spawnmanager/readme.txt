Spawnmanager is a respawn system based in a multi-agent plataform.
The package includes:
- GroupManager: this is the script which holds the groups definitions. On request, it sends a random template from the chosen group to the calling process.
- RegionManager: each region has an associated regionmanager. This object is responsible for holding information on actual spawn situation and region num. The control_script of the object, regionmanager.src, is responsible for handling creature respawn. Each region can have multiple groups, each with its own definition, and multiple specials. The specials are isolated templates, with their own definitions.
- SpawnManager: this is the script used to configure and "manage" all the aspects of the groups and regions. Its functionality is defined at command-overview.txt.

Notice that this package is not considered bug free. If you happen to find any bug, or unpleasant behavior of its components, e-mail me.
If there are sugestions, e-mail me.

Adriano Iank - Hawat
aiank@convoy.com.br