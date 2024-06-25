const express = require('express');
const router = express.Router();

const tradeController = require('../controllers/trades');

router.post('/', tradeController.createTrade);

module.exports = router;
