# _KessCoin2_


## About KessCoin
**KessCoin** is an OpenSource cryptocurrency that is made from somebody having a cat, that cats name was Kess.

**KessCoin** uses advanced blockchain technology and SHA256 hashing algorithms.

We do not share transactions with the internet so you can stay anonymous!

## What happens when you make a transaction?

Your transaction gets processed and put into a buffer, once that buffer fills up it gets pushed
to the blockchains pending transactions list, then those pending transactions get pushed into a block.
That’s where the Proof Of Work algorithm comes in, we use what’s called a nonce and change it until we get the write hash.

That’s called mining, once the block is mined you get a reward of 5 **KC** and the block is added to the blockchain.

"Think Twice, Not Once."
- Ian Marco Moffett (Founder of KessCoin)

"Why would i fear what i cannot see"
- Skyde (Co-Founder of KessCoin)

## How do you build KessCoin?
Easy! You need to have `cpp` installed.

### How do you install `cpp`?

**Debian-based Distros**:
`$ sudo apt install g++`

**OpenSuse**:
`$ sudo zypper install -t pattern devel_C_C++`

**Fedora**:
`$ sudo dnf install gcc-c++`

**Arch-Based Distros**:
`sudo pacman -S gcc`
or
`yay -S gcc`

**Windows**:
You *need* to have `scoop` installed for this.
The tutorial on how to install `scoop` is [_here_](https://scoop.sh).
`scoop install gcc`

##### If you did that....
You just need to clone the repo, `cd` into the folder `KessCoin2/core/build` and do `chmod +x build.sh`, and then `./build.sh`.
This builds the **core**.
Then you need to go back to the root of the folder, with `cd ..`
Then you `cd` into `util/build` and do `chmod +x build.sh`, and then `./build.sh`.
