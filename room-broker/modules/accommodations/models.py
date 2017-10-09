from django.db import models
from datetime import datetime, timedelta
from django.core.validators import MinValueValidator
from django.contrib.auth.models import User
from django.utils.timezone import now

# Create your models here.


class Photo(models.Model):
    img = models.ImageField(upload_to='/img', null=True)
    name = models.CharField(max_length=45)

    def __str__(self):
        return 'Photo()'.format(self.id)


class Accommodation(models.Model):
    name = models.CharField(max_length=45)
    description = models.TextField(max_length=250)
    address = models.CharField(max_length=45)
    city = models.CharField(max_length=45)
    zip_code = models.CharField(max_length=8)
    country = models.CharField(max_length=45)
    capacity = models.IntegerField(default=1)
    bathrooms = models.IntegerField(default=1)
    rooms = models.IntegerField(default=1)
    price = models.IntegerField(default=0, validators=[MinValueValidator(0, 'Price must be a positive integer')])
    photos = models.ManyToManyField(Photo)

    def __str__(self):
        return 'Accommodation({}, {})'.format(self.id, self.name)


class Listing(models.Model):
    author = models.ForeignKey(User)
    details = models.OneToOneField(Accommodation)
    publication_date = models.DateField(auto_created=True)
    view_count = models.IntegerField(default=0)
    premium_offer = models.BooleanField(default=False)
    expired = models.BooleanField(default=False)

    class Meta:
        ordering = ['publication_date']

    def check_if_expired(self):
        return self.publication_date - datetime.now() >= timedelta(days=7)

    def __str__(self):
        return 'Listing({}, {}, {})'.format(self.id, self.author.id, self.details.id)

