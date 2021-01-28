<x-app>

<div class="lg:flex-1 lg:mx-10" style="max-width: 700px">
    <header class="mb-6" style="position: relative">
        <img 
        src="/images/banner.png" 
        alt="user-banner"
        class="mb-4"
        style="border-radius: 20px"
        >

        <div class="flex justify-between items-center mb-4">
            <div>
                <h2 class="font-bold text-2xl mb-0">{{ $user->name }}</h2>
                <p class="text-sm">Signed up {{$user->created_at->diffForHumans() }}</p>
            </div>

            <div>
                <a href="" class="bg-gray-100 rounded-full border border-gray-300 py-2 px-4 text-black-200 text-sm mr-2">Edit Profile</a>
                <a href="" class="bg-blue-500 rounded-full shadow py-2 px-4 text-white text-sm">Follow Me</a>
            </div>
        </div>

        <p class="text-sm">
            I am a student who won't ever graduate since I'm quite stupid KEK
        </p>

        <img src="{{ $user->getAvatar(150) }}" 
                alt="avatar"
                class="rounded-full mr-2 absolute"
                style="top:38%; left: calc(50% - 75px);"
            >

    </header>

    @include('_timeline', ['tweets' => $user->tweets])

</div>

</x-app>
