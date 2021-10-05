-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get a look at all the tables in the db
.schema

-- Find the crime
SELECT * FROM crime_scene_reports WHERE year = 2020 AND month = 07 AND day = 28 AND street = "Chamberlin Street";

/*Found the crime, description: Theft of the CS50 duck took
place at 10:15am at the Chamberlin Street courthouse. Interviews
were conducted today with three witnesses who were present at
the time — each of their interview transcripts mentions the courthouse.*/

-- Find the interviews from this crime
SELECT * FROM interviews WHERE year = 2020 AND month = 07 AND day = 28 AND transcript LIKE "%courthouse%";

/*
161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/

-- Look at security footage for cars leaving courthouse
SELECT activity, license_plate, minute FROM courthouse_security_logs WHERE year = 2020 AND month = 07 AND day = 28 AND hour = 10 AND minute >= 5 AND minute <= 25 AND activity = "exit";

/*
activity | license_plate | minute
exit | 5P2BI95 | 16
exit | 94KL13X | 18
exit | 6P58WS2 | 18
exit | 4328GD8 | 19
exit | G412CB7 | 20
exit | L93JTIZ | 21
exit | 322W7JE | 23
exit | 0NTHK55 | 23*/

-- Look for theif at the ATM in Fifer street
SELECT * FROM atm_transactions WHERE year = 2020 AND month = 07 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "WITHDRAW";

/*
id | account_number | year | month | day | atm_location | transaction_type | amount
246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35 */

-- Locate theif call log (called as they were leaving the courhouse)
SELECT * FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60;

/*
id | caller | receiver | year | month | day | duration
221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54 */

-- Search people table for matching caller phone numbers and license plate
SELECT id, name, passport_number FROM people WHERE people.phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60) AND people.license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 07 AND day = 28 AND hour = 10 AND minute >= 5 AND minute <= 25 AND activity = "exit");

/*
id | name | passport_number
398010 | Roger | 1695452385
514354 | Russell | 3592750733
560886 | Evelyn | 8294398571
686048 | Ernest | 5773159633 */
--passport number set (1695452385, 3592750733, 8294398571, 5773159633)

-- Now we have four suspects and their passport numbers
-- Search for outgoing flights and get passport numbers
SELECT * FROM passengers JOIN flights ON passengers.flight_id = flights.id WHERE flights.year = 2020 AND flights.month = 07 AND flights.day = 29 AND passengers.passport_number IN (SELECT passport_number FROM people WHERE people.phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60) AND people.license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 07 AND day = 28 AND hour = 10 AND minute >= 5 AND minute <= 25 AND activity = "exit"));

/*
flight_id | passport_number | seat | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
18 | 3592750733 | 4C | 18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0
36 | 1695452385 | 3B | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
36 | 5773159633 | 4A | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
36 | 8294398571 | 6C | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 */

-- Great, all four em flew out the following day, except Russel flew alone
-- Three suspects are now Roger, Evelyn, and Ernest
-- Search ATM withdrawals for these three suspects
SELECT * FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE people.name IN ("Roger", "Evelyn", "Ernest") AND atm_transactions.account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 07 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw");

/*
id | name | phone_number | passport_number | license_plate | account_number | person_id | creation_year | id | account_number | year | month | day | atm_location | transaction_type | amount
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X | 49610011 | 686048 | 2010 | 39 | 49610011 | 2020 | 7 | 26 | Fifer Street | withdraw | 10
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X | 49610011 | 686048 | 2010 | 267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50 */

-- Ernest was the only suspect to withdraw money on that day.  He is the theif

-- Now lets find out where he went
SELECT * FROM airports WHERE id = 4;
/*
id | abbreviation | full_name | city
4 | LHR | Heathrow Airport | London
*/
-- He went to London

-- Find accomplice.  Accomplice's phone number is (375) 555-8161
SELECT * FROM people WHERE phone_number = "(375) 555-8161";
/*
id | name | phone_number | passport_number | license_plate
864400 | Berthold | (375) 555-8161 |  | 4V16VO0
*/
