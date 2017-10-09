from django.conf.urls import url
from django.contrib.auth.decorators import login_required, permission_required
from . import views

urlpatterns = [
    # ../
    url(r'^$', views.ListingListView.as_view(), name='listing_list'),

    url(r'^add/$', login_required(views.ListingCreateView.as_view()), name='listing_create'),

    # ../4
    url(r'^(?P<pk>[0-9]+)/$', views.ListingDetailView.as_view(), name='listing_detail'),

    url(r'^(?P<pk>[0-9]+)/$', views.ListingUpdateView.as_view(), name='listing_update'),

    url(r'^(?P<pk>[0-9]+)/delete/$', views.ListingDeleteView.as_view(), name='listing_delete'),
]