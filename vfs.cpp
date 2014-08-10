#include <fstream>
#include <iostream>
#include <string>
#include <functional>

struct stream {
	void *begin, *end, *current;
};

struct details {
	std::string url;
	std::string name;
	unsigned offset;
	unsigned size;
};

struct stats {
	double mem_peak, mem_used;
	double cpu_load;
	unsigned hits;
};

struct asset {
	stream api;
	stats usage;
	unsigned kind;
	details info;
	vec<int> used_by;
};

// to_vfs_hash( uri );
// to_vfs_hash( path );
// to_vfs_hash( arya );

struct vfs_hash {
	template<typename T>
	vfs_hash( const T &t )
	{}
};

struct vfs {
	using callback = std::function<void(const std::string &)>;

	vfs()
	{}

	bool mount( const std::string &anchor, const std::string &path, const callback &add = callback(), const callback &del = callback() )  {
		// for each resource in path {
		// find wildcard, remove absolute path
		// add to anchor path
		// }
		// add callbacks
		return true;
	}

	asset load( const std::string &resource ) const {
		return asset();
	}

	asset preload( const std::string &resource, const callback &ok, const callback &fail = callback() ) {
		return asset();
	}

	bool sync() {
		return true;
	}

	// references & management
	void link( int id, const std::string &name )
	{}
	void link( const std::string &name, int id )
	{}
	void unlink( int id, const std::string &name )
	{}
	void unlink( const std::string &name, int id )
	{}

	void unlink( int id ) 
	{}
	void unlink( std::string name )
	{}



	// push(level)
	//    entity.load bla bla
	// pop()
};

int main() {

	// as you keep adding to bottom, bottom lines have higher priority
	// lowest
	// low
	// high
	// highest...

	// 0) archivers { folders, http server, zip archive }; streams { files, sockets, deflate }
	// basic operations
	// toc()
	// seek()
	// download()
	// upload()
	// open(), close(), write(), read()...

	// 1) create pipes for our program requeriments
	// input assets may be downloaded->unzipped->decrypted or read_from_disk->unzipped->decrypted
	// output assets are always encrypted->zipped->written to disk
	/*
	pipe flow;
	flow.push_in( {read, unzip, decrypt} );
	flow.push_in( {download, unzip, decrypt} );
	flow.push_out( {encrypt, zip, write} );
	data = flow.in( data );
	data = flow.out( data );
	*/

	// 2) mount real and virtual folders into filesystem
	// syntax (mount point,scandirs,callback in,callback out)

	vfs fs;

	fs.mount("levels/", "ro/lev*");
	fs.mount("sounds/", "ro/**.mpc;ro/**.ogg;rw/*.mpc");
	// also can be mounted per ARYA profile tags
	fs.mount("sprites/", "sprites.zip/**#iphone*.png;sprites.zip/**#low*.*" );

	// 3) create placeholders by patterns
	// syntax( rule, resource, on(entity) callback )

	fs.placeholder("sprites/**", "checked.png");
	fs.placeholder("texts/*", "loremipsum.txt");
	fs.placeholder("sounds/*", "wilhelm.wav");
	fs.on(any other missing,"*",[]{assert()});

	// 3a) create linkage libraries
	fs.lib("level1", "data1.png;banner1.png;*1.png");
	fs.lib("level2", "levels/2/*" );
	fs.lib("level3", "sounds/3/*" );
	//so you can preload levels too
	fs.preload("level4");
	//and purge them
	fs.purge("level4");
	//or rewind them
	fs.rewind("level4");

	// 3b) create asset dependencies
	fs.dependency("enemy.iqm", "enemy.tga");
	//

	// 3c) create lods
	fs.lod("enemy.iqm", "enemy.md3", "enemy.md2");
	fs.lod("close.ai","near.ai","far.ai");

	// 4) resolve assets
	// if found, return data
	// if not found return placeholder data if found, else collapse

	stream &asset = fs.find("sky#png#iphone");
	entity skybox = 100;
	skybox.use<texture>( asset.data(), asset.size() );

	// 5) explicit management
	vfs.find("sky.png") -> entities: 100,130,299
	vfs.find(100) -> sky.png, face.png, biped.iqm
	assert( vfs.find("sky.png").hits > 0 );
	// 
	vfs.purge("sky.png");
	vfs.purge(100);

	vfs.purge(); // purge all used & unused resources
	vfs.gc();    // purge all unused resources

	// 6) scope management
	// menu
	vfs.push(stage menu)
	vfs.preload(bg.png,buttons.png)

	vfs.stage(player)
	vfs.preload(list(player))

	vfs.push(stage level)
	vfs.preload(list(level1))

	{
		auto blocker = vfs.stage("player-costumes");
		vfs.preload(listof(player));
		vfs.preload(listof(soundof(player)));
	}

	while( vfs.is_pending() )
	{}

	auto missing = vfs.all_missing();
	vfs.purge(missing);

	if(player.dies()) vfs.restart(level);
	if(next level) vfs.emplace(level);
	if(go to menu) vfs.back()
	if(quit) vfs.popall()/purge

}