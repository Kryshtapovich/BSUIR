from app import db

user_to_city = db.Table('user_to_city',
                        db.Column('user_id', db.BIGINT, db.ForeignKey('user.user_id')),
                        db.Column('city_id', db.BIGINT, db.ForeignKey('city.city_id')))


class User(db.Model):
    user_id = db.Column(db.BIGINT, primary_key=True)
    user_name = db.Column(db.String(32))
    password = db.Column(db.String(15))
    is_banned = db.Column(db.Boolean, default=False)
    help_table = db.relationship('City', secondary=user_to_city,
                                 backref=db.backref('users', lazy='dynamic'))

    def __init__(self, user_id, user_name, password):
        self.user_id = user_id
        self.user_name = user_name
        self.password = password


class City(db.Model):
    city_id = db.Column(db.Integer, primary_key=True)
    city_name = db.Column(db.String(30))

    def __init__(self, city_name):
        self.city_name = city_name


db.create_all()
