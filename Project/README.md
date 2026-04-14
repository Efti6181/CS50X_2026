# Deadlock Detection Simulator

#### Video Demo: https://youtu.be/W4eCUt1S724?si=GDUJjQrZ_8_E1VCS

#### Description:

Deadlock Detection Simulator is a web-based application that simulates the Resource Allocation Graph used in Operating Systems to detect deadlocks. The purpose of this project is to help students understand how deadlock occurs and how it can be detected using graph cycle detection algorithms.

This project was created as the final project for CS50x. The program allows the user to enter processes and resources in the form of edges, then the system builds a directed graph and checks whether a deadlock exists. If a cycle is found in the graph, the system reports that a deadlock has occurred. Otherwise, the system is safe.

The application is built using Python, Flask, SQLite, HTML, and CSS. The backend logic is written in Python, while the frontend uses HTML and CSS to display the user interface. SQLite is used to store edges entered by the user so that the graph can be saved and displayed later.

Files in this project:

app.py  
This is the main Flask application. It handles routing, form input, database connection, and calls the deadlock detection algorithm. It receives edges from the user, stores them in the database, and checks for deadlock.

deadlock.py  
This file contains the DeadlockDetector class. It implements a directed graph and uses Depth First Search (DFS) to detect cycles. If a cycle is detected, the program returns that a deadlock exists.

database.db  
This SQLite database stores all edges entered by the user. Each edge contains a source node and a destination node.

templates/index.html  
This file contains the main user interface. The user enters edges here and clicks the detect button.

templates/saved.html  
This page displays saved edges from the database in table format.

static/style.css  
This file contains the design of the website, including colors, fonts, and layout.

Design choices:

I decided to use Flask because it allows easy connection between Python and HTML. I used SQLite because it is simple and does not require installation of a server. I used DFS cycle detection because it is the standard method for detecting deadlocks in a resource allocation graph.

I also decided to allow users to type edges manually instead of creating a complex graphical interface. This makes the program simpler while still demonstrating the concept clearly.

Challenges:

One challenge was implementing cycle detection correctly. Another challenge was connecting the database with Flask and saving edges properly. I also had to make sure the program resets the graph every time the user runs detection.

Future improvements:

In the future, this project can be improved by adding a graphical visualization of the resource allocation graph. Another improvement would be allowing users to add processes and resources using buttons instead of text input. It is also possible to add Banker's Algorithm to check safe state.

Conclusion:

This project demonstrates how deadlock detection works using graph theory. It shows the relationship between processes and resources and how circular waiting causes deadlock. This project helped me understand operating system concepts better while also improving my skills in Python, Flask, SQL, and web development.