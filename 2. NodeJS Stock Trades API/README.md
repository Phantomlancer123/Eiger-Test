# NodeJS: Stock Trades API

In this challenge, your task is to implement a simple REST API to manage a collection of stock trades. (check the project.zip archive that comes with this exercise)

Each trade is a JSON entry with the following keys:

    id: The unique trade ID. (Integer)
    type: The trade type, either 'buy' or 'sell'. (String)
    user_id: The unique user ID. (Integer)
    symbol: The stock symbol. (String)
    shares: The total number of shares traded. The traded shares value is between 1 and 100 shares, inclusive. (Integer)
    price: The price of one share of stock at the time of the trade. (Integer)
    timestamp: The epoch time of the stock trade in milliseconds. (Integer)

Here is an example of a trade JSON object:
```JSON
{
    "id": 1,
    "type": "buy",
    "user_id": 23,
    "symbol": "ABX",
    "shares": 30,
    "price": 134,
    "timestamp": 1531522701000
}
```

The task is to implement a model for the Trade object and the REST service that exposes the /trades endpoint, which allows for managing the collection of trade records in the following way:

POST request to /trades:

    creates a new trade
    expects a JSON trade object without an id property as a body payload. If the shares value is out of the accepted range [1, 100], or the type value is invalid (i.e., not 'buy' or 'sell'), the API must return error code 400. Besides those cases, you can assume that the given payload is always valid.
    adds the given trade object to the collection of trades and assigns a unique integer id to it. The first created trade must have id 1, the second one 2, and so on.
    the response code is 201, and the response body is the created trade object

GET request to /trades:

    returns a collection of all trades
    the response code is 200, and the response body is an array of all trade objects ordered by their ids in increasing order
    optionally accepts query parameters type and user_id, for example /trades?type=buy&user_id=122. All these parameters are optional. In case they are present, only objects matching the parameters must be returned.

GET request to /trades/<id>:

    returns a trade with the given id
    if the matching trade exists, the response code is 200 and the response body is the matching trade object
    if there is no trade with the given id in the collection, the response code is 404 with the body having the text `ID not found`
DELETE, PUT, PATCH request to /trades/<id>:
    the response code is 405 because the API does not allow deleting or modifying trades for any id value

You should complete the given project so that it passes all the test cases when running the provided unit tests. The project by default supports the use of the SQLite3 database.

Note: You are expected to choose the ORM you want to use and initialize the connection of the Database in the file `connection.js`. The following ORMs/Databases are available for use out of the box:

1. Sequelize with SQLITE
2. Mongoose with MongoDB

Example requests and responses

POST request to /trades/
Request body:
```JSON
{
   "type": "buy",
   "user_id": 1,
   "symbol": "AC",
   "shares": 28,
   "price": 162,
   "timestamp" : 1591514264000
}
```

The response code is 201, and when converted to JSON, the response body is:
```JSON
{
   "id": 1,
   "type": "buy",
   "user_id": 1,
   "symbol": "AC",
   "shares": 28,
   "price": 162,
   "timestamp" : 1591514264000
}
```

This adds a new object to the collection with the given properties and id 1. If the share value is not in the range [1, 100], or the type value is not 'buy' or 'share', then the response code is 400.

GET request to /trades/

The response code is 200, and when converted to JSON, the response body (assuming that the below objects are all objects matching the filter) is as follows:
```JSON
[
   {
      "id": 1,
      "type": "buy",
      "user_id": 1,
      "symbol": "AC",
      "shares": 28,
      "price": 162,
      "timestamp" : 1591514264000
   },
   {
      "id": 2,
      "type": "sell",
      "user_id": 1,
      "symbol": "AC",
      "shares": 28,
      "price": 162,
      "timestamp" : 1591514264000
   }
]
```

GET request to /trades/?type=buy

The response code is 200, and when converted to JSON, the response body (assuming that the below objects are all objects matching the filter) is as follows:
```JSON
[
   {
      "id": 1,
      "type": "buy",
      "user_id": 1,
      "symbol": "AC",
      "shares": 28,
      "price": 162,
      "timestamp" : 1591514264000
   }
]
```

GET request to /trades/?user_id=2

The response code is 200, and when converted to JSON, the response body (assuming that the below objects are all objects matching the filter) is as follows:
```JSON
[
   {
      "id": 1,
      "type": "buy",
      "user_id": 2,
      "symbol": "AC",
      "shares": 28,
      "price": 162,
      "timestamp" : 1591514264000
   },
   {
      "id": 2,
      "type": "sell",
      "user_id": 2,
      "symbol": "AC",
      "shares": 28,
      "price": 162,
      "timestamp" : 1591514264000
   }
]
```

GET request to /trades/1/

Assuming that the object with id 1 exists, then the response code is 200 and the response body, when converted to JSON, is as follows:
```JSON
{
   "id": 1,
   "type": "buy",
   "user_id": 1,
   "symbol": "AC",
   "shares": 28,
   "price": 162,
   "timestamp" : 1591514264000
}
```

If an object with id 1 doesn't exist, then the response code is 404 with the response body having the text `ID not found`.

DELETE request to /trades/1/

The response code is 405 and there are no particular requirements for the response body.

