<div class="bg-blue-100 rounded-2xl py-4 px-6">
    <h3 class="font-bold text-xl mb-4">Following</h3>

    <ul>
        @foreach (auth()->user()->follows as $user)
            <li class="mb-4">
                <div >
                    <a href="/users/{{ $user->name }}" class="flex items-center text-sm">
                        <img 
                        src="{{ $user->getAvatar(40) }}" 
                        alt="avatar"
                        class="rounded-full mr-2"
                        >
                        {{ $user->name }}
                    </a>
                </div>
            </li>
        @endforeach
    </ul>
</div>