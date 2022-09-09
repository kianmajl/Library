
# Library Management System
This is my final project for the advanced programming course at the University of Isfahan. It has been written with Qt using QWidgets.
It is provided users with a user-friendly GUI and a login system with two types of permissions.
## Usage

For running and modifying this project you should have installed Qt Creator, Then open `Library.pro` and build the project. 

Also, you can use the executable file from [here](https://github.com/kianmajl/Library/releases).
## Examples of use

- Login/Signup

    After running the program, you will see the authentication form.
    You can signup/login with your username and password.
        
    The program has a default admin user with this credential:
    ```
    username: admin
    password: admin
    ```
    
    <img src="https://user-images.githubusercontent.com/22191288/187410883-ab7a0263-76a1-454b-8c07-b38cfb181312.jpg" alt="Authentication Form" width="362px" higth="263px">


- Admin Dashboard

    After logging in with an admin user, you can access the admin dashboard.

    <img src="https://user-images.githubusercontent.com/22191288/187414007-141040cc-e5c0-41a3-81dc-a510f6a309d9.jpg" alt="Admin Dashboard" width="600px" higth="450px">

    This panel has below features:
	
	<details>
	<summary>Books List</summary>
	
	 You can add, edit, and delete a book in this panel. Also, you can filter and sort the books based on their different parameters.
	 
	<img src="https://user-images.githubusercontent.com/22191288/187424962-0e40500a-ddb7-4e00-9f6b-d3ff2ec8d451.jpg" alt="Admin Dashboard | Books List" width="600px" higth="450px">
	
	</details>
	
	<details>
	<summary>Groups List</summary>
	
	 You can add, edit, and delete a group in this panel. Also, you can see books and their details in each group.
	 
	<img src="https://user-images.githubusercontent.com/22191288/187428734-f89cd38d-3cba-47d4-8de7-c7b5f957c0b8.jpg" alt="Admin Dashboard | Groups List" width="600px" higth="450px">
	
	</details>
	
	<details>
	<summary>Users List</summary>
	
	 You can edit(change password, give admin access) and delete a user in this panel.
	 
	 **Note:** Passwords are stored with the `SHA-256` algorithm. 

	<img src="https://user-images.githubusercontent.com/22191288/187431288-cbf364e4-1d30-49ca-8fff-18bc25bef1b8.jpg" alt="Admin Dashboard | Users List" width="600px" higth="450px">
	
	</details>
	
	<details>
	<summary>Issued Books List</summary>
	
	 In this panel, You can view books that have been issued by users.

	 **Note:** If the expiration date of a record is close, the row color of it will be yellow and if it is passed, the color will be red.

	<img src="https://user-images.githubusercontent.com/22191288/187437092-34573821-72af-4e2b-91e5-f61da5d583bc.jpg" alt="Admin Dashboard | Issued Books List" width="600px" higth="450px">
	
	</details>
	
	<details>
	<summary>Messaging System</summary>

	 You can send messages to other users and receive messages from them too.

	<img src="https://user-images.githubusercontent.com/22191288/187445265-fd35addb-0e60-4305-8b89-897be8971fb6.jpg" alt="Inbox Panel" width="600px" higth="450px">
	
	<img src="https://user-images.githubusercontent.com/22191288/187445410-07ff1c4f-0539-4d2a-a1a7-0fa490b2d0bc.jpg" alt="Outbox Panel" width="600px" higth="450px">

	<img src="https://user-images.githubusercontent.com/22191288/187445497-0b4b16c1-73ba-4bfe-8ed7-e11b721fab05.jpg" alt="Compose Panel" width="600px" higth="450px">

	</details> 


- User Dashboard

    After logging in, you can access your dashboard.

    <img src="https://user-images.githubusercontent.com/22191288/187434624-f874185c-e9a8-45d8-a64b-3653f5122113.jpg" alt="User Dashboard" width="600px" higth="450px">

    This panel has below features:
	
	<details>
	<summary>Books List</summary>
	
	 You can see and issue books in this panel. Also, you can filter and sort the books based on their different parameters.
	 
	 **Note:** If the expiration date of a book that you have issued has passed, you can not issue a new book!

	<img src="https://user-images.githubusercontent.com/22191288/187447633-5efa7bb1-4b49-4eb3-9379-7b6c410a19a9.jpg" alt="User Dashboard | Books List" width="600px" higth="450px">
	
	</details>
	
	<details>
	<summary>Groups List</summary>
	
	 You can see and search groups of books in this panel. Also, you can see books and their details in each group.
	 
	<img src="https://user-images.githubusercontent.com/22191288/187456289-fd6af0fc-a533-4803-9456-645fd53d6c50.jpg" alt="User Dashboard | Groups List" width="600px" higth="450px">
	
	</details>
	
	<details>
	<summary>Issued Books List</summary>

	 You can see and return books that you have issued in this panel.
	 
	 **Note:** If the expiration date of a record is close, the row color of it will be yellow and if it is passed, the color will be red.
	 
	<img src="https://user-images.githubusercontent.com/22191288/187455641-744681a1-4538-44f7-a0fd-383bf44ef0bc.jpg" alt="User Dashboard | Issued Books List" width="600px" higth="450px">
	
	</details>
	
	
	<details>
	<summary>Messaging System</summary>

	 You can send messages to other users and receive messages from them too.
	 
	 **Note:** If the expiration date of a book that you have issued is closed or passed, the system will send you a message.

	<img src="https://user-images.githubusercontent.com/22191288/187458270-e406cebf-2f1a-4a67-b1ed-0ed5837cbc1a.jpg" alt="Inbox Panel" width="600px" higth="450px">
	
	</details> 
