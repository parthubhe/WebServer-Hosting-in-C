# WebServer-Hosting-in-C
Welcome to the Recipe Management System (RMS) and C-Based HTTP Server project! This repository showcases a simple yet powerful application that combines recipe management features with a lightweight web server built in C, using efficient data structures like Binary Search Trees (BST) and Linked Lists.



📜 Project Overview
The project is designed to manage recipes and serve them as web content efficiently. It consists of two primary components:

Recipe Management System (RMS): A C-based console application that allows users to add, delete, search, sort, and filter recipes stored in a linked list.
C-Based HTTP Server: A simple HTTP server implemented using Winsock on Windows, managing routes with a Binary Search Tree (BST) for quick and efficient content delivery.
🌟 Features
Recipe Management System
Add, Delete, and Display Recipes: Easily manage your collection of recipes.
Search by Name: Quickly find a recipe using a case-insensitive search.
Sort Recipes: Sort by name or time required, in both ascending and descending order.
Filter Recipes: Filter by cuisine or dish type (e.g., breakfast, lunch, dinner).
Save/Load Recipes: Persist recipes to a file and load them on startup.
C-Based HTTP Server
Route Management with BST: Efficiently handle HTTP requests and routes using a Binary Search Tree.
Static Content Serving: Serve HTML, CSS, and images for a complete web-based experience.
Dynamic Recipe Rendering: Render and display recipes from a recipes.txt file in HTML format.
🛠️ Data Structures Used
Binary Search Tree (BST): Used to manage and search routes efficiently for the HTTP server.
Linked List: Used to store and manage recipes, providing flexibility and efficiency for dynamic data operations.
🚀 How to Run
Clone the Repository:
bash
Copy code
git clone https://github.com/yourusername/recipe-management-c-server.git
Compile the Server and RMS:
Use gcc or any C compiler to build the project. A build.bat script is provided for Windows.
Start the Server:
Change the paths of the header files according to you folder.
Run the compiled server executable to start the HTTP server on the specified port.
[command to run the mulltiple files:
gcc -g "E:\downloads_29_10_24\sample_web_Server\cerveur\src\main.c" 
>>     "E:\downloads_29_10_24\sample_web_Server\cerveur\src\HTTP_Server.c" 
>>     "E:\downloads_29_10_24\sample_web_Server\cerveur\src\Response.c" 
>>     "E:\downloads_29_10_24\sample_web_Server\cerveur\src\Routes.c" 
>>      -o "E:\downloads_29_10_24\sample_web_Server\cerveur\src\main.exe" -lws2_32
>>
 ]
 the use ./main.exe in the src folder[cd src]

 
