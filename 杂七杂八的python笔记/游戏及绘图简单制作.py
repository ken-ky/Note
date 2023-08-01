import pygame


def main():
    '''
    0 制作游戏窗口
    1 在窗口中绘图
    2 加载图像
    3 实现动画
    :return:
    '''
    pygame.init()
    screen = pygame.display.set_mode((800, 600))  # 0 screen set
    pygame.display.set_caption('大球恰小球')  # 0 title set
    screen.fill((242, 242, 242))  # 1 设置屏幕填充方法

    # 1 绘制一个圆(参数分别是: 屏幕, 颜色, 圆心位置, 半径, 0表示填充圆)
    pygame.draw.circle(screen, (255, 0, 0,), (100, 100), 30, 0)

    # 1 刷新当前窗口
    pygame.display.flip()

    # 2 通过指定文件名加载图像
    ball_img = pygame.image.load('../stupid_zone/ball.png')

    # 2 在窗口上渲染图像
    screen.blit(ball_img, (50, 50))

    # 3 定义变量来表示小球在屏幕上的位置
    x, y = 50, 50

    running = True  # 0 设置事件一直进行
    while running:
        # 0 从消息队列中获取事件并对事件进行处理
        for event in pygame.event.get():
            if event.type == pygame.QUIT:  # 0 设置退出选项
                running = False

        # 3
        screen.fill(((255, 255, 255)))
        pygame.draw.circle(screen, (255, 0, 0), (x, y), 30, 0)

        # 每隔50毫秒就改变小球的位置再刷新窗口
        pygame.time.delay(50)
        x, y = x + 5, y + 5


if __name__ == '__main__':
    main()
