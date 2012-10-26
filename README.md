What is Funtime?
================

*Funtime* is a pseudo-graphic image editor, which works with *Cursed Image* file format (.cmg).

How to?
=======

You have to move the brush by pressing the arrow keys and perform a few operations, which you can see below.

*Symbol editing:* press *Return*, then press any symbol key you want to appear under the brush.
*Brush painting:* you just need to press *Space*. You can learn, which symbol will be painted by watching the bottom right. Note that this operation can paint colored symbols.
*Changing the brush symbol:* use *'Z'* key and enter desired symbol.
*Changing the brush color:* press *'X'* key and enter an integer value, which must belong to 0-63 range.
*Paint the brush color only:* press *'C'*.
*Paint non-colored brush symbol:* press *'V'*.
*Rectangle:* using brush, get to the position where you want the rect to begin and press *'R'*. Then type the width and heigth of the rect to be painted.
*Text:* use *'T'* and type something. Beware: usage of spaces or tabs in your message are pretty glitchy.
*Erasing:* use the *'E'* key.
*Cutting:* press *'1'* and enter the width and heigth values of image area to be cutted.
*Copying:* same like *Cutting*, but use the *'2'* key.
*Pasting:* just press *'3'*.
*Resolution changing:* use the *'S'* button.
*Load an image:* press *'I'* and type the filename (cancel by typing *'.'*).
*Save an image:* press *'O'* and type the filename. (cancel by typing *'.'*).
You also can update the recently saved file by pressing *'L'*.
You can move the workspace by holding *Shift* and pressing the arrow keys.
*'P'* toggles the bottom panel's visibility.
Press *'Q'* to exit the *Funtime*.

Build Funtime
=============

You need the [Cursed Image library](https://github.com/MEDVEDx64/cursedimage) 0.5.0 or higher, and libncurses development files (not tested on ncurses < 5.7).
Type *'make'* to compile *Funtime*.

License
=======

*Funtime* is a free software and available under the terms of GNU General Public License.
