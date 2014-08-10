#pragma once

/* idea [ref] http://www.reddit.com/r/gamedev/comments/10g6b6/c_managing_game_resources/

- a datestamp of last access time
- a background process that checks to see if an asset hasnt been accessed in a given period of time, it gets purged
- the ability to pre-allocate a list of assets, and mark assets as non-purgable ( so you can preload assets you know you will need )
- a method to purge down to a given size
- a method to purge down to a given date
- a method to download content from website if no local copy is found, or if its damaged/manipulated
*/

class asset2
{
	//const char *data;
	//size_t len;

	// void preload() -> fetch()
	// bool changed()
	// void reload()

	// void stream(0.5s) -> fetch() -> fetch()
	// void stream(500kb)
};

// or:

int preload( asset &, const std::string &url )
{
	// 1) fetch disk://, http:// etc...
	// 2) convert to engine friendly, if needed
	// 3) give a copy, keep original safe (until purge() is called) (good idea?) (sharedptr?)
	//
	// async done when asset.size() > 0
    // if resource is not found it gives a placeholder instead
	//  (always gives a valid asset)
	//  yellow/black texture
	//  #TEXT text
	//  AABB box etc
}

// watchman, package manager, library

void sync(id) {
    // check id
    auto found = pending.find(id);
    if( found != pending.end() ) {
        found.second->wait();
        pending.erase(found);
    }
}

void sync(date) {
    // check pendings
    for( any : pending ) {
        if( date >= any.date ) {
            sync( any.id );
        }
    }
}

void sync() {
    // all pendings
    sync( now() );
}
