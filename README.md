# Converter
Sample Document Converter

This is a sample program for Markzware.

Thank you for taking the time to do our technical test. It consists of two parts:

A Windows coding project
A couple of technical questions

If you have any questions or concerns please feel free to reach out to me. Either through email or Slack.


Windows Coding Project
The task is to create a Windows application that displays a window with configurable settings. The application should allow the user to choose an InDesign ("indd" extension) file from a standard Open dialog window before converting the file using the user-defined configuration settings. 



For testing, the conversion is merely copying the existing file and changing the extension.



The configuration options should include:

Where to save the converted file? (document location or a specific path). 
What format to export as? (IDML, PNG, JPG) 
What to do after the conversion? (Reveal in Finder, Open in default application)]

Task Requirements
Feel free to spend as much or as little time on the exercise, as you like. Please be sure that the following requirements are met.

Please complete the user stories below.
Your code should compile and run in one step.
Please provide a built Windows application.

User Stories
As a user, I want to convert my InDesign files into IDML files, so I can edit them in QuarkXPress.
As a user, I want to be able to configure the application, so I can control the conversion process. 


Acceptance criteria

Given a user-supplied path to an InDesign file, a copy is created using the current configuration settings.



Technical questions:

How long did you spend on the coding test? About 8 hours.

What would you add to your solution if you had more time? Unit testing, more documentation.

What was the most useful feature that was recently added to one of your favorite programming languages? It has been a long time
since I programmed in Visual Studio. I tried to do a minimal installation and found that parts were missing. I wanted to use
MFC and a more class and dialog based application. I had a the basis done quite quickly, but then I wanted to delve into some of
the functionality that was new to me.

Where to save the converted file? (document location or a specific path). 

  After selecting the choosing the file to convert, the default document destination is filled from the source folder. This can be
  changed by using the Destination button.

What format to export as? (IDML, PNG, JPG)

  The formats are in an Output Type combo box. I added .pdf as the default to produce a document that I can open automatically 
  upon the file conversion. I included a file, Matplotlib.indd. This is actually a .pdf file. When I simulate converting it, it
  can open automatically with a PDF viewer.
  
What to do after the conversion? (Reveal in Finder, Open in default application)]
  
  I added an Open Upon Conversion checkbox that can be selected to open the file in the default application.
