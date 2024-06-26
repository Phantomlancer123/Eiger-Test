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

exports.getTrades = async (req, res) => {
  try {
    const { type, user_id } = req.query;
    const where = {};

    if (type) {
      where.type = type;
    }

    if (user_id) {
      where.user_id = user_id;
    }

    const trades = await Trade.findAll({ where, order: [['id', 'ASC']] });
    res.status(200).json(trades);
  } catch (error) {
    res.status(500).send();
  }
};

exports.getTradeById = async (req, res) => {
  try {
    const trade = await Trade.findByPk(req.params.id);

    if (!trade) {
      return res.status(404).send('ID not found');
    }

    res.status(200).json(trade);
  } catch (error) {
    res.status(500).send();
  }
};

exports.methodNotAllowed = (req, res) => {
  res.status(405).send();
};
  