# https://cs50.harvard.edu/x/2020/tracks/web/finance/#specification
# Specification

## register
Complete the implementation of register in such a way that it allows a user to register for an account via a form.

Require that a user input a username, implemented as a text field whose name is username. Render an apology if the user’s input is blank or the username already exists.
Require that a user input a password, implemented as a text field whose name is password, and then that same password again, implemented as a text field whose name is confirmation. Render an apology if either input is blank or the passwords do not match.
Submit the user’s input via POST to /register.
INSERT the new user into users, storing a hash of the user’s password, not the password itself. Hash the user’s password with generate_password_hash Odds are you’ll want to create a new template (e.g., register.html) that’s quite similar to login.html.

Once you’ve implemented register correctly, you should be able to register for an account and log in (since login and logout already work)! And you should be able to see your rows via phpLiteAdmin or sqlite3.

## quote
Complete the implementation of quote in such a way that it allows a user to look up a stock’s current price.

    Require that a user input a stock’s symbol, implemented as a text field whose name is symbol.
    Submit the user’s input via POST to /quote.
    Odds are you’ll want to create two new templates (e.g., quote.html and quoted.html). When a user visits /quote via GET, render one of those templates, inside of which should be an HTML form that submits to /quote via POST. In response to a POST, quote can render that second template, embedding within it one or more values from lookup.

## buy
Complete the implementation of buy in such a way that it enables a user to buy stocks.

    Require that a user input a stock’s symbol, implemented as a text field whose name is symbol. Render an apology if the input is blank or the symbol does not exist (as per the return value of lookup).
    Require that a user input a number of shares, implemented as a text field whose name is shares. Render an apology if the input is not a positive integer.
    Submit the user’s input via POST to /buy.
    Odds are you’ll want to call lookup to look up a stock’s current price.
    Odds are you’ll want to SELECT how much cash the user currently has in users.
    Add one or more new tables to finance.db via which to keep track of the purchase. Store enough information so that you know who bought what at what price and when.
        Use appropriate SQLite types.
        Define UNIQUE indexes on any fields that should be unique.
        Define (non-UNIQUE) indexes on any fields via which you will search (as via SELECT with WHERE).
    Render an apology, without completing a purchase, if the user cannot afford the number of shares at the current price.
    You don’t need to worry about race conditions (or use transactions).

Once you’ve implemented buy correctly, you should be able to see users’ purchases in your new table(s) via phpLiteAdmin or sqlite3.


## index
Complete the implementation of index in such a way that it displays an HTML table summarizing, for the user currently logged in, which stocks the user owns, the numbers of shares owned, the current price of each stock, and the total value of each holding (i.e., shares times price). Also display the user’s current cash balance along with a grand total (i.e., stocks’ total value plus cash).

    Odds are you’ll want to execute multiple SELECTs. Depending on how you implement your table(s), you might find GROUP BY HAVING SUM and/or WHERE of interest.
    Odds are you’ll want to call lookup for each stock.

## sell
Complete the implementation of sell in such a way that it enables a user to sell shares of a stock (that he or she owns).

    Require that a user input a stock’s symbol, implemented as a select menu whose name is symbol. Render an apology if the user fails to select a stock or if (somehow, once submitted) the user does not own any shares of that stock.
    Require that a user input a number of shares, implemented as a text field whose name is shares. Render an apology if the input is not a positive integer or if the user does not own that many shares of the stock.
    Submit the user’s input via POST to /sell.
    You don’t need to worry about race conditions (or use transactions).

## history
Complete the implementation of history in such a way that it displays an HTML table summarizing all of a user’s transactions ever, listing row by row each and every buy and every sell.

    For each row, make clear whether a stock was bought or sold and include the stock’s symbol, the (purchase or sale) price, the number of shares bought or sold, and the date and time at which the transaction occurred.
    You might need to alter the table you created for buy or supplement it with an additional table. Try to minimize redundancies.

## personal touch
Implement at least one personal touch of your choice:

    Allow users to change their passwords.
    Allow users to add additional cash to their account.
    Allow users to buy more shares or sell shares of stocks they already own via index itself, without having to type stocks’ symbols manually.
    Require users’ passwords to have some number of letters, numbers, and/or symbols.
    Implement some other feature of comparable scope.

# Testing
Be sure to test your web app manually too, as by

    inputting alpabetical strings into forms when only numbers are expected,
    inputting zero or negative numbers into forms when only positive numbers are expected,
    inputting floating-point values into forms when only integers are expected,
    trying to spend more cash than a user has,
    trying to sell more shares than a user has,
    inputting an invalid stock symbol, and
    including potentially dangerous characters like ' and ; in SQL queries.

# Staff’s Solution
You’re welcome to stylize your own app differently, but here’s what the staff’s solution looks like!

https://finance.cs50.net/

Feel free to register for an account and play around. Do not use a password that you use on other sites.

It is reasonable to look at the staff’s HTML and CSS.

# Hints
Within cs50.SQL is an execute method whose first argument should be a str of SQL. If that str contains named parameters to which values should be bound, those values can be provided as additional named parameters to execute. See the implementation of login for one such example. The return value of execute is as follows:

    If str is a SELECT, then execute returns a list of zero or more dict objects, inside of which are keys and values representing a table’s fields and cells, respectively.
    If str is an INSERT, and the table into which data was inserted contains an autoincrementing PRIMARY KEY, then execute returns the value of the newly inserted row’s primary key.
    If str is a DELETE or an UPDATE, then execute returns the number of rows deleted or updated by str.

If an INSERT or UPDATE would violate some constraint (e.g., a UNIQUE index), then execute returns None. In cases of error, execute raises a RuntimeError.

    Recall that cs50.SQL will log to your terminal window any queries that you execute via execute (so that you can confirm whether they’re as intended).
    Be sure to use named bind parameters (i.e., a paramstyle of named) when calling CS50’s execute method, a la WHERE name=:name. Do not use f-strings, format or + (i.e., concatenation), lest you risk a SQL injection attack.
    If (and only if) already comfortable with SQL, you’re welcome to use SQLAlchemy Core or Flask-SQLAlchemy (i.e., SQLAlchemy ORM) instead of cs50.SQL.
    You’re welcome to add additional static files to static/.
    Odds are you’ll want to consult Jinja’s documentation when implementing your templates.
    It is reasonable to ask others to try out (and try to trigger errors in) your site.
    You’re welcome to alter the aesthetics of the sites, as via
        https://bootswatch.com/,
        https://getbootstrap.com/docs/4.1/content/,
        https://getbootstrap.com/docs/4.1/components/, and/or
        https://memegen.link/.

# FAQs
## ImportError: No module named ‘application’
By default, flask looks for a file called application.py in your current working directory (because we’ve configured the value of FLASK_APP, an environment variable, to be application.py). If seeing this error, odds are you’ve run flask in the wrong directory!

## OSError: [Errno 98] Address already in use
If, upon running flask, you see this error, odds are you (still) have flask running in another tab. Be sure to kill that other process, as with ctrl-c, before starting flask again. If you haven’t any such other tab, execute fuser -k 8080/tcp to kill any processes that are (still) listening on TCP port 8080.

## How to Submit
Execute the below from within your finance directory, logging in with your GitHub username and password when prompted. For security, you’ll see asterisks (*) instead of the actual characters in your password.

submit50 cs50/problems/2020/x/tracks/web/finance