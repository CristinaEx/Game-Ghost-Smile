from PIL import Image

def resize(pic_name,size = (960,640),save_name = 'test.png'):
    img = Image.open(pic_name)
    img = img.resize(size)
    img.save(save_name)

def cut(pic_name,x,y,width = 960,height = 640,save_name = 'test.png'):
    img = Image.open(pic_name)
    img = img.crop((x,y,x+width,y+height))
    img.save(save_name)

if __name__ == '__main__':
    resize('1601.png')
    