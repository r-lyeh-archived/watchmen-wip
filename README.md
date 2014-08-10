watchmen
========

Virtual filesystem to pipe, monitor and process your datas. Written in C++11.

### motivation

- http/folder mounting and watching
- if asset "corner-left.png" has changed, mark all libraries that include "corner-left.png" as touched
- then send reload message to all entities that use touched libraries
- then send reload message to all games that use touched entities
- then send reload message to all applications that loaded touched games
- and so on...

### roadmap

- hash functions [arya,file,zippath] -> number -> physical file offset,size
- a/sync loading api (load and preload/sync)
- hot reloading <-> implies folder/file watching, also resource dependencies and libraries
- automatic libraries : bimap : resources in entity E, entities with resource X.
- vfs pipe in / out
- vfs link,unlink,assign,use,bind
- rw > ro [data], $cache > $home, 
- output sqlite/lmdb
- folder mounting
- unzip files
- motivation:

```c++
int main()
{
	// sync api
	const auto data = wm.load(hash);

	// async api
	{
		wm sync("stage"); // raii sync
		wm.preload(hash, [ok], [fail]);
	}
	const auto data = wm.load(hash);

	// rw is monitored, ro is not
	set<entity> entities;
	for( auto &any : wm.files_in("rw/**") ) {
		if( any.just_added() || any.just_updated() || any.just_deleted() ) {
			for( auto &file : any.dependencies() ) {
				entities.insert_set( entities_using(file) );
			}
		}
	}
	on( entities, RELOAD );
}
```

```
// arya #platform#consumer#season#name#rev#type

ns arya {
	struct settings {
		std::string platforms[];
		std::string consumers[];
		std::string contexts[];
		std::string names[];
		std::string revisions[];
		std::string types[];
	};
	struct profile {
		unsigned platform, consumer, context, name, revision, type;
	};
	struct hash {
		hash(file, [profile = blank() | #forcetags]);
		hash(url, [profile = blank() | #forcetags]);
		hash(number, [profile = blank() | #forcetags]);
		hash(hash, [profile = blank() | #forcetags]);
		hash(fuzzy name, [profile = blank() | #forcetags]);
		operator <, ==, != 
	};
	struct collection {
		void include(hash, [profile = blank() | #forcetags]);
		void remove(hash, [profile = blank() | #forcetags]);
		bool maybe(hash, [profile = blank() | #forcetags]); // bloom filter: yes/no
	};
}

settings.platforms = "#w32#iphone";
settings.consumers = "#text#texture#music";
settings.contexts = "#regular#xmas";
settings.revisions = "#0#1#2#3";
settings.types = "#png#mpc"

std::string profile = "#iphone*#xmas#1"; //get previous stable settings

collection test;
test.include("sky.png");
test.include("w32/sky.png","#w32");



```
