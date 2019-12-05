# -*- coding:utf-8 -*-
from PIL import Image, ImageDraw, ImageFont

img = Image.new('RGB', (1080, 300), color = (73, 109, 137))


fnt = ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf', 48, encoding='utf-8')
d = ImageDraw.Draw(img)
d.text((5,5), u"Bonjour, voici ce que notre OCR est capable\nde renvoyer. Pour tout essai, veuillez\nconsulter notre cheffe de groupe. \nAvec amour, attention, et larmes, \nFifty shades of grayscale par L'essai.", font = fnt, fill=(255,255,0))
#d.text((5,5), u"\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\n\x6f\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\n\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\n\x4e\x4f\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\n\x2e\x21\x3f\x2b\x28\x29\x2f\x27\xc3\xa9\xc3\xa8\xc3\xaa\xc3\xa0\xc3\xa2\xc3\xae\xc3\xb4\xc3\xb9\xc3\xbb\n\x31\x32\x33\x34\x35\x36\x37\x38\x39\x30", font = fnt, fill=(255,255,0))

img.save('pil_text.bmp')
