Recquirements: nwnx_object and Malishara DM Stage Wand

With this you can import stages on your online server (very limited: no names, no descriptions, no scripts...absolute positions) so its better import the placeables in a special area and store them with the DM Stage Wand for future use.

I'll suppose you have tag based script enabled in your module:

1. Create a new module, with all the haks of your server, with an area with tag dm_explanada (a flat one)
2. Create an item with tag it_g_escenario, identified, with the property Unique Power Self Only, unlimitted use
3. Drop this item in the middle of the area 
4. Create and copy the it_g_escenario.nss on your server module
5. Get a copy of gffmatch.exe from http://www.kivinen.iki.fi/nwn/downloads.html
6. Create a folder "util" on your "My Documents/Neverwinter Nights" directory
7. Copy gffmatch.exe and the file escenario.bat to the util directory
8. Build the scenery in your new module with all the placeables you want
9. Save but don't close the module (the unpacked module should be in the modules/temp0 folder)
10. Double click the escenario.bat file of the util directory: a file escenario.txt should be created
11. Open the file excenario.txt and select then copy the whole content of the file
12. Paste it on the identified description of the item it_g_escenario on the floor of your new module
13. Load the module and grab the item with your DM avatar
14. Go to your server and use the object "in an area big enough" the placeable will be created: the placeables are created at the same absolute positions of your newly created module, so depending on the dimenssioos of the servre area maybe you'll hace to look for them.
15. Now you can use the Malishara DM stage wand to save the objects in a Stage Wand and use them where you want



 
