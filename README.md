# badref  -  v0.1.1
A music referencer, but written kinda badly.
The sole purpose is immediate switching between different versions of the same audio.


Main Features:
- Loading all audio files named as "[test 000] artist - song name" and displaying them as one audio file in the playlist.
- Displaying the versions loaded alongside the loaded file, allowing version switching during playback.
- Placing markers and naming them and looping them, or reading markers if rendered in from a daw.

Additional Features:
- Adding comments and to-do checkboxes to an autio file or a specific version.
- Keeping history of to-do completion and extracting it to a text file.

- - - -
## Building badref
### build tool: [nob.h](https://github.com/tsoding/nob.h) by [Tsoding](https://github.com/tsoding)
Before building, I encourage reading the usage of the tool at the nob.h repo.

#### Linux - Debian-Based:

Using a terminal:
```
cc -o nob nob.c &&
./nob
```

Run badref with `./badref`. Additionally, you could move the executable to your binaries directory:
```
sudo mv badref /usr/local/bin/
```

and run it directly with the command `badref`.
