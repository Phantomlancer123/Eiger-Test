const Trade = require('../models/trades');

exports.createTrade = async (req, res) => {
  try {
    const { type, user_id, symbol, shares, price, timestamp } = req.body;

    if (shares < 1 || shares > 100 || (type !== 'buy' && type !== 'sell')) {
      return res.status(400).send();
    }

    const trade = await Trade.create({ type, user_id, symbol, shares, price, timestamp });
    res.status(201).json(trade);
  } catch (error) {
    res.status(500).send();
  }
};