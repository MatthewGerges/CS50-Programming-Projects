-- Keep a log of any SQL queries you execute as you solve the mystery.

--NEST QUERIES AND JOIN TABLES

--1)
SELECT description FROM crime_scene_reports WHERE year = 2020 and month = 7 and day = 28 and street = "Chamberlin Street";
-- Running this sql command gives us more details about the mysetery. These details can be used to run SQL queries and retrieve info from other tables
/*
"Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with 
three witnesses who were present at the time — each of their interview transcripts mentions the courthouse."

The above information tells us to query the transcripts
*/

--2)
SELECT name, transcript FROM interviews where year = 2020 and month = 7 and day = 28;

/*

<<
Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car 
in the courthouse parking lot and drive away. 
If you have security footage from the courthouse parking lot, 
you might want to look for cars that left the parking lot in that time frame.

Eugene | I don't know the thief's name, but it was someone I recognized. 
Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street 
and saw the thief there withdrawing some money.

Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. 
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. 
The thief then asked the person on the other end of the phone to purchase the flight ticket.
>>
*/

--1st query based on Ruth's information
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 and month = 7 and day = 28 and hour = 10 and minute > 15 and minute < 25);
-- This select query is based on the fact that Ruth told us that within 10 minutes (10:15 - 10:25) of the theft she saw a thief going into a car


--2nd query is based on Eugene's info
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 and month = 7 and day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));
-- Eugene told us that the thief withdrew some money from the atm on Fifer street on the same day of the roberry (went into the fiftyville database under atm_transactions table to see houw the transaction_types were written)



--3rd query process is based on Raymond's info
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 and month = 7 and day = 28 and duration < 60);
--the robber called someone on the day of the theft for less than a minute, this query gives us the name of the caller (the robber) based on their phone number and call time



-- The 4th query is based on Raymond's second piece of information: 
-- We are told that the thief will take a flight out of fiftyville tomorrow
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 and month = 7 and day = 29 ORDER BY hour ASC LIMIT 1));
-- Raymond tells us that the thief will take the earliest flight in the morning which is why we order the flights in terms of time (earliest hour, minute)

-- *****We can combine all 4 of the queries above by using AND to see if the robber's name is IN each query
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 and month = 7 and day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw")) and phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 and month = 7 and day = 28 and duration < 60) and people.passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 and month = 7 and day = 29 ORDER BY hour, minute ASC Limit 1)) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 and month = 7 and day = 28 and hour = 10 and minute > 15 and minute < 25); 

-- The above query tells us that the thief is Ernest

-- WHO WAS THE ACCOMPLICE??
-- We know the accomplice was the person who the thief called on the day of the theft (who bought him the plane ticket)
-- The accomplice is the RECEIVER on the phone call whose CALLER was Ernest
SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2020 and month = 7 and day = 28 and duration < 60 and caller IN (SELECT phone_number FROM people WHERE name = "Ernest")) LIMIT 1;

--The above query tells us that the accomplice's name is Berthold



-- Query for the destination of the flight that the thief went on: we know he's leaving fiftyville and we know Ernest - the thief is one of the passengers
SELECT abbreviation, full_name, city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE year = 2020 and month = 7 and day = 29 and id IN(SELECT flight_id FROM passengers WHERE passport_number IN(SELECT passport_number FROM people WHERE name = "Ernest")));

-- The above query tells us that the thief attempted to escape to London


