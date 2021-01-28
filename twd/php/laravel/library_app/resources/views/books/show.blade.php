@extends('layout')

@section('content')
    <!-- Content -->
    <section>
        <header class="main">
            <h1>{{$book->title}}</h1>
        </header>

        <span class="image main"><img src="/images/pic11.jpg" alt="" /></span>

        <!-- This allows to render something if there are no data for that genre -->
        @forelse ($book->genres as $genre)
            <a href="/genres/{{ $genre->name }}" class="button">{{ $genre->name }}</a>
            @empty
            <p>This book seems to have no genres associated yet :(</p>
        @endforelse
        <hr>
        <h2><a href="/authors/{{ $book->user->id }}"> {{ $book->user->name}}</a></h2>

        <p>{{$book->description}}</p>

    </section>

</div>
</div>
@endsection