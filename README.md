# scrot_to_pb
Fair warning this is sorta shit since I hacked it together at 4:30am woo!

You'll need these packages to use it.
`sudo pacman -S xclip firefox scrot curl gcc`

Then run `make all` in the cloned folder.
That will make a folder called bin with the binary file inside it.
I put a link to the binary in ~/bin/ then in my i3 config I set mod+s exec ~/bin/stpb
You can make a symbolic link like this. Just change the paths to the ones you'd like to use.
`ln -s /path/to/scrot_to_pb/bin/stpb /home/username/bin/stpb`

If you don't use firefox or don't want it to open firefox edit the code and recompile with g++
