import discord
import asyncio
import requests

DISCORD_BOT_TOKEN = 'NTM0MzM2ODU3NTg0OTU5NDk4.Dx4H4A.7Aj98bPxsXUMsA2yaNGNRlxqfZc'

BTC_PRICE_URL_coinmarketcap = 'https://api.coinmarketcap.com/v1/ticker/bitcoin/?convert=RUB'

client = discord.Client()

@client.event
async def on_ready():
    print('Logged in as')
    print(client.user.name)
    print(client.user.id)
    print('------')

@client.event
async def on_message(message):
    if '@Flare' in message.content:
        print('Anton was @sobakked')
        btc_price_usd, btc_price_rub = get_btc_price()
        await client.send_message(message.channel, 'USD: ' + str(btc_price_usd) + ' | RUB: ' + str(btc_price_rub))
    if 'www.youtube.com' in message.content:
	phrases = {
	    1: 'Дай угодаю... Опять видос от Андрея?',
	    2: 'Опа, видосик подъехал',
	    3: 'Срочно всем смотреть!!! 3, 2, 4...',
	    4: 'Опять смотреть эту хуйню(9((',
	    5: 'Где, что, куда смотреть?',
	    6: 'qq'
	}
	await client.send_message(message.channel, phrases[random.randint(1, 5)])

def get_btc_price():
    r = requests.get(BTC_PRICE_URL_coinmarketcap)
    response_json = r.json()
    usd_price = response_json[0]['price_usd']
    rub_rpice = response_json[0]['price_rub']
    return usd_price, rub_rpice

client.run(DISCORD_BOT_TOKEN)
