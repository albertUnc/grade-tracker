# grade-tracker
### Utility for students to track their grades
This is for people who don't have electronic/online grades system in their school/country, like myself. This helps me because i can track all my grades in it and the main point is that you can get your average off the grades easily.

For now, all grades are 1-10 so if you have percents in your country, just round them and divide by 10, if you have any other like 1-5 number grades, use a calculator to convert it to 1-10 or if the biggest mark you can get is under 10, you can just use those and it will still work, but it only lets you put in full numbers 1-10 in this version.

# How to use:

There are 2 main ways to use this.

## C++ terminal-based application
You start it, loads all grades from disk to memory, from there you can do all kinds of stuff like delete and add grades, view all grades and averages. Make sure to use the built-in Quit option, don't just close it or interrupt the task, since that will cause all updates to not be saved.
This one will be pretty obvious to use since you just start the app and it will list options for you, you just choose and input your stuff.

## Python command utility
This isn't an app you start and use, this is like a terminal based tool, so each thing you do is a seperate command in your terminal.
How to use: You will need python installed on your computer, along with a few packages.
How you can install python and the package needed:

### Install python
On Windows, download the official python installer, run it and make sure you check add python to PATH and that you download the pip package manager. After that, open up a new powershell window, and run `python --version`, it's supposed to output something like 3.x. Then, run `pip install platformdirs` and wait for the installation to finish.

On linux debian: Python is installed by default, you can install the package by running `sudo apt install python3-platformdirs`. This will ask for your password, if you don't have administrator acces, try `apt install python3-platformdirs`, this should work without asking for a password but the download may not be successful.

### How to use
How to use:
On windows: Open powershell or cmd, get to the folder that has grade-tracker.py in it and type `python grade-tracker.py`, don't run it yet. After this you will need to put all the arguments for the command utility (see later down)
On linux: Open a terminal, get to the folder grade-tracker.py is in and type `python3 grade-tracker.py`, don't run it yet, you will need to add the arguments after this.

#### Arguments/guide to usage
The first word after grade-tracker.py should be one of these:

`average`: shows average of grades (based on all grades and based on subjects' averages)

`averages`: does the same as average

`list`: shows all grades sorted by subject

`subject`: you can delete a subject with this. The full usage is `subject remove "Subject name"` if the subject's name has spaces in it, you have to wrap it in "", if not, its not neccesarry. `subject` by itself does nothing and will just error out.

`grade`: you can add and remove grades, usage:
`grade add Subj 8`: adds a grade to subject called Subj and grade value of 8. if the subject doesn't already exist, it gets created.
`grade remove Subj 7`: removes a grade from Subj subject, if there are multiple 7 grades, it just removes 1.

## Which one should i choose?
I would say the terminal-based c++ application is much better. It is faster, easier to use, and there is a pre-compiled version for Linux so you don't need to download anything other than the app, but you can use both. These 2 edit the same grades.json file on your computer, so they aren't 2 seperate apps, just 2 seperate tools accessing the same data.
(but this may only be because i don't like python nearly as much as i like c++)

# Upcoming:
#### planning to do in next updates
-Adding support to set any max and min value for grades, so it doesn't only work 1-10

-Adding pre-built windows version for the c++ app alongside Linux support

-Fixing as much bugs as i can find/people report

-Adding backups/protection so if you have a lot of data of grades it doesn't accidentally get destroyed

-Probably either fully removing or improving the python tool a lot (For example adding support to run it without installing anything else)

## Support me
#### Discord: @albertunc or https://discord.com/users/1509130123851337748
#### Check out my other projects! github.com/albertUnc
#### Report bugs if you find any, and give me tips/ideas for this app, but other projects too!
