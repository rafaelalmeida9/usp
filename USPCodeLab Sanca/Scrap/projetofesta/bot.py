#!/usr/bin/env python
# pylint: disable=C0116,W0613
# This program is dedicated to the public domain under the CC0 license.

"""
Simple Bot to reply to Telegram messages.

First, a few handler functions are defined. Then, those functions are passed to
the Dispatcher and registered at their respective places.
Then, the bot is started and runs until we press Ctrl-C on the command line.

Usage:
Basic Echobot example, repeats messages.
Press Ctrl-C on the command line or send a signal to the process to stop the
bot.

$ pip install python-telegram-bot --upgrade
"""

#Bot: @festa_sanca_bot

import logging

from telegram import Update, ForceReply
from telegram.ext import Updater, CommandHandler, MessageHandler, Filters, CallbackContext

SEMANA_ATUAL = 6

# Enable logging
logging.basicConfig(
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s', level=logging.INFO
)

logger = logging.getLogger(__name__)


# Define a few command handlers. These usually take the two arguments update and
# context.
def start(update: Update, context: CallbackContext) -> None:
    """Send a message when the command /start is issued."""
    user = update.effective_user
    update.message.reply_markdown_v2(
        fr'Hi {user.mention_markdown_v2()}\!',
        reply_markup=ForceReply(selective=True),
    )


def help_command(update: Update, context: CallbackContext) -> None:
    """Send a message when the command /help is issued."""
    update.message.reply_text('Help!')


def echo(update: Update, context: CallbackContext) -> None:
    """Echo the user message."""
    update.message.reply_text("""Para ficar por dentro dos rolês digite /festa""")

def festa(update: Update, context: CallbackContext) -> None:
	f = open("roles.txt", "r", encoding='utf-8')
	semana = f.readlines()
	update.message.reply_text('Festas da semana:\n' + semana[SEMANA_ATUAL])

def main() -> None:
	
	# arq = open("roles.txt", "r", encoding='utf-8')
	# lista = []
	# lista = arq.read()
	# print(lista)

	"""Start the bot."""
	# Create the Updater and pass it your bot's token.
	updater = Updater("5788621192:AAFisrmH7WcfjtVCoyJmY_w9T8d7-XV16bM")

	# Get the dispatcher to register handlers
	dispatcher = updater.dispatcher

	# on different commands - answer in Telegram
	dispatcher.add_handler(CommandHandler("start", start))
	dispatcher.add_handler(CommandHandler("help", help_command))
	dispatcher.add_handler(CommandHandler("festa", festa))


	# on non command i.e message - echo the message on Telegram
	dispatcher.add_handler(MessageHandler(Filters.text & ~Filters.command, echo))

	# Start the Bot
	updater.start_polling()

	# Run the bot until you press Ctrl-C or the process receives SIGINT,
	# SIGTERM or SIGABRT. This should be used most of the time, since
	# start_polling() is non-blocking and will stop the bot gracefully.
	updater.idle()


if __name__ == '__main__':
    main()