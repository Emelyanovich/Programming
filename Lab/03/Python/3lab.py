from tkinter import Tk, Label, Frame, Button, LEFT, Y
from PIL import Image, ImageTk
from os import path
from random import randint


class Tile:
    def __init__(self, name, size):
        resources_folder = path.realpath(path.dirname(__file__) + '/Pictures')
        self._image_path = resources_folder + f'/{name}.png'
        self.normal
        self.size = size

        self.taken = [None for _ in range(10)]

    @property
    def rgba(self):
        self.image = Image.open(self._image_path).convert('RGBA')
        return self

    @property
    def normal(self):
        self.image = Image.open(self._image_path)
        return self

    def take_img(self, i):
        if not self.taken[i]:
            taken_img = self.cut(i)
            taken_photo = ImageTk.PhotoImage(taken_img)
            self.taken[i] = taken_photo
            return taken_photo

        else:
            return self.taken[i]

    def cut(self, i):
        step = self.size
        xs = 1
        xe = self.size
        ys = (i - 1) * step
        ye = i * step
        taken = self.image.crop((xs, ys, xe, ye))

        return taken


class ViewTiles:
    def __init__(self):
        self.aqua_ball = FieldTile('ball-aqua', 60)
        self.blue_ball = FieldTile('ball-blue', 60)
        self.green_ball = FieldTile('ball-green', 60)
        self.pink_ball = FieldTile('ball-pink', 60)
        self.red_ball = FieldTile('ball-red', 60)
        self.violet_ball = FieldTile('ball-violet', 60)
        self.yellow_ball = FieldTile('ball-yellow', 60)

        self.cell = FieldTile('cell-bgr', 69)
        self.page = FieldTile('page-bgr', 128)


tiles = None


class Position:
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y


def differ(pos1, pos2):
    return Position(pos1.x - pos2.x, pos1.y - pos2.y)


class ViewCell(Label):
    def __init__(self, master, row, col, field):
        self.ball_tile = None
        self.backed = None
        self.field: list[list[ViewFieldCell]] = field

        super().__init__(master, image=tiles.cell.take_img(1), borderwidth=0)
        self.grid(row=row, column=col)
        self.bind('<Button-1>', self.on_click)
        self.click_handler = None
        self.pos = Position(col, row)
        self.is_prev = False

    def put_ball(self, ball_tile: FieldTile):
        self.to_blend_bg_ball(1, ball_tile, 1)

    def select_ball(self):
        self.to_blend_bg_ball(2, self.ball_tile, 1)

    def unselect_ball(self):
        self.to_blend_bg_ball(1, self.ball_tile, 1)

    def to_blend_bg_ball(self, bg_tile_num, ball_tile, ball_tile_num):
        bg = tiles.cell.rgba.cut(bg_tile_num)
        ball = ball_tile.rgba.cut(ball_tile_num)
        new_ball = Image.new('RGBA', bg.size)
        new_ball.paste(ball, (7, 6))
        backed = Image.alpha_composite(bg, new_ball)
        backed_photo = ImageTk.PhotoImage(backed)
        self.backed = backed_photo
        self.ball_tile = ball_tile
        self.config(image=backed_photo)

    def clear(self):
        self.backed = None
        self.config(image=tiles.cell.take_img(1))

    def on_click(self, event):
        if self.click_handler:
            self.click_handler(self, event)

    @property
    def is_free(self):
        return not self.backed

    def sibling_in(self, direction: Position):
        rev_dir = Position(-direction.x, -direction.y)
        new_pos = differ(self.pos, rev_dir)
        if (new_pos.x < 0 or new_pos.y < 0 or
                new_pos.y > len(self.field) - 1 or new_pos.x > len(self.field[0]) - 1):
            return None
        return self.field[new_pos.y][new_pos.x]


class ViewGameInfo:
    def __init__(self, master):
        self.lines = Label(master, font=("Google Sans", 20), bg='#454545', fg='#ffffff')
        self.lines.grid(row=1, column=1, columnspan=3, pady=10)
        self.score = Label(master, font=("Google Sans", 20), bg='#454545', fg='#ffffff')
        self.score.grid(row=2, column=1, columnspan=3)
        self.update_lines(0)
        self.update_score(0)

    def update_lines(self, value):
        self.lines.config(text=f'Линии {value}')

    def update_score(self, value):
        self.score.config(text=f'Счёт: {value}')


class GameControls:
    def __init__(self, master):
        Label(master, height=1, bg='#454545').grid(row=3, column=1, columnspan=3)
        self.step = Button(master, text="Сделать ход", font=("Google Sans", 15), bg='#515156', fg='white', padx=2,
                           pady=1, relief='raised')
        self.step.grid(row=6, column=1, columnspan=3, pady=10)
        self.new_game = Button(master, text="Новая игра", font=("Google Sans", 15), bg='#515156', fg='white', padx=2,
                               pady=1, relief='raised')
        self.new_game.grid(row=10, column=1, columnspan=3, pady=10)


class GameHint(list):
    def __init__(self, master):
        super().__init__()
        Label(master, height=2, bg='#454545').grid(row=7, column=1, columnspan=3)
        Label(master, text='Подсказка:', font=("Google Sans", 15), bg='#454545', fg='white').grid(row=7, column=1,
                                                                                                  columnspan=3, pady=4)
        self.model = []
        for i in range(3):
            self.append(Label(master, bg='#454545'))
            self.model.append(None)
            self[i].grid(row=9, column=1 + i)

    def update(self: list, three_balls: list):
        i = 0
        for ball in three_balls:
            self[i].config(image=ball.take_img(5))
            self.model[i] = ball
            i += 1


class GameInfo:
    def __init__(self, master):
        master.config(bg='#454545')
        self.controls = GameControls(master)
        self.hint = GameHint(master)
        self.info = ViewGameInfo(master)


class Interface:
    def __init__(self, field_size):
        global tiles

        self.root = Tk()
        self.root.title('Линии')
        width = 68 * field_size + 200
        height = 68 * field_size + 10
        screen_width = self.root.winfo_screenwidth()
        screen_height = self.root.winfo_screenheight()

        x_coordinate = int((screen_width / 2) - (width / 2))
        y_coordinate = int((screen_height / 2) - (height / 2))
        self.size = Position(width, height)
        self.root.geometry("{}x{}+{}+{}".format(width, height, x_coordinate, y_coordinate))

        tiles = ViewFieldTiles()
        self.tiles = tiles

        self.root.config(bg='#454545')

        self.field_frame = Frame(self.root)
        self.field_frame.pack(side=LEFT)

        self.info_frame = Frame(self.root)
        self.info_frame.pack(side=LEFT, fill=Y)
        self.info = GameInfo(self.info_frame)

        self.field = []
        for row in range(field_size):
            self.field.append([])
            for col in range(field_size):
                cell = ViewFieldCell(self.field_frame, row, col, self.field)
                self.field[row].append(cell)

        self.game_over = Label(self.info_frame, fg='white', bg='#454545', text="Игра окончена",
                               font=("Google Sans", 19), padx=2, pady=1)

    @property
    def game_over_visibility(self):
        pass

    @game_over_visibility.setter
    def game_over_visibility(self, visible: bool):
        if visible:
            self.game_over.grid(row=11, column=1, columnspan=3)
        else:
            self.game_over.grid_forget()

    def render(self):
        self.root.mainloop()


class ModelField(list):
    def __init__(self, field: list):
        super().__init__()
        self.field = field

        size = len(field)

        def get_square_dialog(square_shift_x, square_shift_y, square_size, reverse=False):
            nonlocal field

            dialog = []
            for j in range(square_size):
                if not reverse:
                    zx = j
                    zy = j
                else:
                    zx = square_size - 1 - j
                    zy = j
                dialog.append(field[square_shift_y + zy][square_shift_x + zx])

            return dialog

        rows = field

        cols = [[] for cell in field[0]]
        for row in field:
            i = 0
            for cell in row:
                cols[i].append(cell)
                i += 1

        main_dialogs = [get_square_dialog(0, 0, size)]
        for i in range(5, size):
            k = size - i
            main_dialogs.append(get_square_dialog(k, 0, i))
            main_dialogs.append(get_square_dialog(0, k, i))

        sub_dialogs = [get_square_dialog(0, 0, size, True)]
        for i in range(5, size):
            k = size - i
            sub_dialogs.append(get_square_dialog(k, k, i, True))
            sub_dialogs.append(get_square_dialog(0, 0, i, True))

        self.rows = rows
        self.cols = cols
        self.main_dialogs = main_dialogs
        self.sub_dialogs = sub_dialogs


class Model:
    def __init__(self, view_field: Interface):
        self.view = view_field
        self.state = 'ball not selected'
        self.selected = None
        self.score = 0
        self.lines = 0
        self.field = ModelField(view_field.field)

        self.restart()

        view_field.info.controls.new_game.bind('<Button-1>', self.restart)
        view_field.info.controls.step.bind('<Button-1>', self.step)

        for row in self.view.field:
            for cell in row:
                cell.click_handler = self._cell_click_handler

    def restart(self, event=None):
        self.view.game_over_visibility = False
        self._clear_field()
        self.gen_hint()
        self.step()
        self.view.info.info.update_score(0)
        self.view.info.info.update_lines(0)
        self.state = 'ball not selected'

    def step(self, event=None):
        self.use_hint()
        self.gen_hint()

    def gen_hint(self):
        balls = []
        for i in range(3):
            balls.append(self._random_ball())
        self.view.info.hint.update(balls)

    def use_hint(self):
        hint = self.view.info.hint

        free = self._field_free_cells()

        for i in range(2, -1, -1):
            if len(free) - i <= 1:
                self.game_over()
                return
            else:
                cell = self._random_from(free)
                cell.put_ball(hint.model[i])
                free.pop()

    def game_over(self):

        self.view.game_over_visibility = True

    @staticmethod
    def _random_from(list_of):
        return list_of[randint(0, len(list_of) - 1)]

    def _random_ball(self):
        field_tiles = self.view.tiles
        balls = [
            field_tiles.aqua_ball,
            field_tiles.blue_ball,
            field_tiles.green_ball,
            field_tiles.pink_ball,
            field_tiles.red_ball,
            field_tiles.violet_ball,
            field_tiles.yellow_ball
        ]

        return self._random_from(balls)

    def _field_free_cells(self):
        free = []
        field = self.view.field
        for row in field:
            for cell in row:
                if cell.is_free:
                    free.append(cell)
        return free

    def _clear_field(self):
        field = self.view.field

        for row in field:
            for cell in row:
                cell.clear()

    def _cell_click_handler(self, cell: ViewFieldCell, event):

        if cell.is_free:
            if self.state == 'ball not selected':
                pass
            elif self.state == 'ball selected':
                reachable = self._cells_reachable(self.selected, cell)

                if reachable:
                    cell.put_ball(self.selected.ball_tile)

                    self.selected.unselect_ball()
                    self.selected.clear()
                    self.selected = None

                    self.state = 'ball moved'

                    lines = self._check_all_lines()

                    for line in lines:
                        self.lines += 1
                        self.view.info.info.update_lines(self.lines)

                        for cell in line:
                            cell.unselect_ball()
                            cell.clear()

                            self.score += 2
                            self.view.info.info.update_score(self.score)

                    self.state = 'ball not selected'

                    if len(lines) == 0:
                        self.step()

                else:
                    pass
        else:
            if self.state == 'ball not selected':
                self.state = 'ball selected'
                self.selected = cell
                cell.select_ball()
            elif self.state == 'ball selected':
                self.selected.unselect_ball()
                self.selected = cell
                cell.select_ball()

    def _cells_reachable(self, a: ViewFieldCell, b: ViewFieldCell, print_check_way=False):

        def reset_cells_prev():
            field = self.view.field
            for row in field:
                for cell in row:
                    cell.is_prev = False

        def step_all_directions(from_cell: ViewFieldCell, target: ViewFieldCell):
            player_steps = []

            left = Position(1, 0)
            right = Position(-1, 0)
            up = Position(0, 1)
            down = Position(0, -1)
            for direction in [up, down, left, right]:
                sibling = from_cell.sibling_in(direction)

                if not sibling:
                    continue

                if sibling == target:
                    return True
                else:
                    if sibling.is_free and not sibling.is_prev:
                        sibling.is_prev = True
                        if print_check_way:
                            sibling.to_blend_bg_ball(1, self.view.tiles.yellow_ball, 6)
                        player_steps.append(sibling)

                    elif sibling.is_free and sibling.is_prev:
                        if print_check_way:
                            sibling.to_blend_bg_ball(1, self.view.tiles.green_ball, 6)

            return player_steps

        steps = [a]

        while True:
            new_steps_storage = []

            for step in steps:
                new_steps = step_all_directions(step, b)

                if new_steps is True:
                    reset_cells_prev()
                    return True
                else:
                    new_steps_storage += new_steps

            if len(new_steps_storage) == 0:
                reset_cells_prev
                return False
            steps = new_steps_storage

    def _check_all_lines(self):

        def check_field_lines(field_lines):
            sequences = []

            for line in field_lines:
                sequence = []
                prev_color = None

                def reset_sequence(color, field_cell=None):
                    nonlocal sequence, prev_color

                    if len(sequence) > 4:
                        sequences.append(sequence)

                    prev_color = color
                    sequence = [field_cell] if field_cell else []

                for cell in line:
                    if cell.is_free:
                        reset_sequence(None)
                        continue

                    else:
                        curr_color = cell.ball_tile

                        if prev_color is None:
                            reset_sequence(curr_color, cell)

                        elif curr_color == prev_color:
                            sequence.append(cell)

                        else:
                            reset_sequence(curr_color, cell)

                reset_sequence(None)

            return sequences

        field_lines = []
        field_lines += check_field_lines(self.field.rows)
        field_lines += check_field_lines(self.field.cols)
        field_lines += check_field_lines(self.field.main_dialogs)
        field_lines += check_field_lines(self.field.sub_dialogs)

        return field_lines


ui = Interface(10)
gameModel = Model(ui)

ui.render()
