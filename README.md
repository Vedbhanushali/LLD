# LLD

URL Shortener
Rate Limiter
Mini Games (Ludo/Chess/Tic-Tac-Toe/Snake-Ladder)
Realtime N-Player Game Engine (Fortnite/CoD)
Online Betting Platforms
Parking Lot System (Multi-storey)
N-Elevator Management System
Ecommerce + Quick Commerce System
Messaging + Notification System
Library Management System
File Upload/Storage System
Online Auction System
Social Media Backend
Distributed File System
Notification Queue System (Pub/Sub Model)
Distributed Caching System
Session Management System
Ticket Reservation System (Movie/Train/Flight)
Video Streaming + Live Streaming Platform
Content Delivery Network
Blogging Platform
Collaborative Document Editing System (Google Docs)
Payment Gateway System
Search Engine Backend
File Compression/Decompression Service
Chat System (WhatsApp)
Content Management System
Job Scheduling System
Distributed Locking System
Social Feed Algorithm (Facebook/Instagram feed)
Rating and Review System (Movie/Product/Service)
Multi-Tenant SaaS Application
Online Judge (CC/CF)
2-Player/N-Player Rating System (Chess/CF - Elo)
Ride Booking System (Uber/OLA/Rapido)
Food Ordering System (Zomato/Swiggy)
Online Learning Platform (Coursera/Udemy)
Log Aggregation System
Customer Support System + Chatbot

## Swiggy

- Revision example SOLID and other principles - done
- Snake Ladder - done
- Cron System - done
- warehouse management system for swiggy - done
- Design a food-order matching system. - WIP

## first

Questions for Round 3 (Interview LLD):

Design your own "Cron System" :
The user must input the command it wants to be executed and the epoch time when he wants to execute it.
The command can be a unix commad
Design the LLD of Snake and Ladder game.

## second

The first question was to desing our own "Cron Job" like system.

I said that we will take input from user which will have "Command" and "Epoch time".
Store this command and time in DB along with isActive and UserId
I will run a service which will iterate the DB every second and take out all the commands that are active below the current time.
I will execute each command one-by-one
Counter question: Why one-by-one? Can't we do all at the same time?
One by one because the following commands can be dependant on previous commands. For example: "cd bhool-bhuliya" will depend on mkdir "bhool-bhuliya"
Input from Interviewer: Assume that dependency doesn't exist.
Okay. Then I will execute the commands all at a time.
After execution completion I will mark all the command's isActive = false.
Counter question: What if multiple servers are doing this job? How will you prevent duplicate execution of each command?
I will block the DB from read operations till the commands finishes executing (sensed that it is wrong since other services might need to read the data for some different purpose).
After lot of thinking I said I will use Queue system to execute (intended to use priority queue). The server will consume slots of commands.
Counter question: What if the command fails?
I will log any error which comes in the way. After completion of slot. Will try executing again or put on the queue.
Counter question: What if error is not know? Suppose power shut down etc.
I will use queue system which waits for aknowledgement.
Counter question: But then this will increase the latency since copying can take a lot of time.
This is where I fumbled.
One more question: How will you monitor this system.
After execution of each command I will push the details on another queue will be consumed by logger server to print the logs.
---------------------------**************************************-----------------------------------

Question 2: Design a snake and ladder game (LLD with classes) just the overview.

made a Game class. First made a Map<Integer, Integer>. this will make the snakes (from and to) and ladders (from and to)
a function addShortcuts(int from, int to) to manage the snakes and ladder.
made a Player class having name and email (UK)
made Player Manager having Array, function to add player
After this I did something due to which I think I was not selected. In initializeGame function of Game, I wanted to iterate over the players List and make a map againt storing email and position (-1 on initialization). This player list will be injected on the Game constructor and will set the Game's playerList.
a chance function initialized to 0.
move function -> will generate the random numer of dice and add to the player in the map. And will increase the chance. If chance reached playerList.length it willl be 0 again.
Counter Quesiton: Don't you think that Game class has too many responsibilities?
This is was the final nail in the coffin. I moved this player list and move function to the PlayerManager class.
Moral: Before jumping to the Design pattern, let's read about the SOLID principles and implement it enough number of times. My prior experience has majorly been in NodeJS but that can't be the excuse.

Final Remarks:

I know Snake and Ladder is basic but I fumbled.
Just after the interview I did the design (with implementation).
This interview was quiet motivating for me. Will try to shift from JavaScript to Java.
I am actually laid off curently and the gap is increasing. Looks like tough time build character.
Result: Received the rejection email just few hours ago.

## third

Design warehouse management system for Swiggy Instamart. Design APIs, DB schemas, and a high level diagram. Focus on managing inventory and being consistent across different systems.

## fourth

System Design: “Design a food-order matching system.” I outlined services, databases, caches, and explained trade-offs for consistency vs. latency.
