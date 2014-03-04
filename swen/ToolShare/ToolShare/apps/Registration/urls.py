from django.conf.urls import patterns, url

from ToolShare.apps.Registration import views

urlpatterns = patterns('',
    url(r'^$', views.index, name='index'),
)